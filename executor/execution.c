/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:17:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/17 18:27:14 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                    pipeline(t_ast *left, t_ast *right, char **env)
{
    // printf("[%s]->[%s]-->%d\n", left->tokens->info, right->tokens->info, left->parent->type);
    pid_t   pid1;
    pid_t   pid2;
    int     pfd[2];
    int		stat_loc;

    // printf("!!!\n");
    if (pipe(pfd) < 0)
        pipe_fd_error();
    if ((pid1 = fork()) == -1)
        fork_error();
    else if (pid1 == 0)
    {
        printf("***\n");
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        close(pfd[0]);
        printf("???\n");
        char **w_splited;

        w_splited = NULL;
        w_splited = array_assign(left, w_splited);
        w_splited = parsed_word(w_splited, env);
        if (w_splited[0] != NULL)
            env = ft_core(w_splited, env);
        if (w_splited)
            free_2darray(&w_splited);
        exit(0);
        // if_redir(t_ast *left);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        close(pfd[1]);
        char **new;
        
        new = NULL;
        new = array_assign(left, new);
        new = parsed_word(new, env);
        if (new[0] != NULL)
            env = ft_core(new, env);
        if (new)
            free_2darray(&new);
        exit(0);
    }
    waitpid(pid1, &stat_loc, WUNTRACED);
    waitpid(pid2, NULL, WUNTRACED);
    left = NULL;
    right = NULL;
    return ;
    // // printf("[%s->%s]\n", left->tokens->info, right->tokens->info);
}

void                    exec_pipe(t_ast *ast, t_shell *shell, char **w_splited, char **env)
{
    if (!ast->left)
    {
        pipeline(ast, ast->parent->right, env);
        return ;
    }
    exec_pipe(ast->left, shell, w_splited, env);
}

void                    exec_semi(t_ast *ast, t_shell *shell, char **env, char **w_splited)
{
    execution(ast->left, shell, env, w_splited);
    execution(ast->right, shell, env, w_splited);
}

char                    **execution(t_ast *ast, t_shell *shell, char **env, char **w_splited)
{
    if (!ast)
        return (env);
    else if (ast->type == T_SEMI)
        exec_semi(ast, shell, env, w_splited);
    else if (ast->type == T_PIPE)
        exec_pipe(ast, shell, w_splited, env);
    else if (ast->type != T_PIPE && ast->type != T_SEMI)
    {
        w_splited = array_assign(ast, w_splited);
        w_splited = parsed_word(w_splited, env);
        if (w_splited[0] != NULL)
            env = ft_core(w_splited, env);
        if (w_splited)
            free_2darray(&w_splited);
    }
    return (env);
}
