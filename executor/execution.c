/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:17:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/18 00:30:15 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                    right_pipe(int fd[2], t_ast *right, char **env)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        char **w_splited;
        w_splited = NULL;
        w_splited = array_assign(right, w_splited);
        w_splited = parsed_word(w_splited, env);
        ft_available_command(w_splited, env);
        exit(0);
    }
    else
    {
        close(fd[1]);
        waitpid(pid, NULL, 0);
    }
}

void                    pipeline(t_ast *left, t_ast *right, char **env)
{
    int     fd[2];
    pid_t   pid;

    if ((pipe(fd)) == -1)
        pipe_fd_error();
    if ((pid = fork()) == -1)
        fork_error();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        char **w_splited;
        w_splited = NULL;
        w_splited = array_assign(left, w_splited);
        w_splited = parsed_word(w_splited, env);
        ft_available_command(w_splited, env);
        exit(0);
    }
    else
    {
        waitpid(pid, NULL, WUNTRACED);
        right_pipe(fd, right, env);
    }
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
    {
        exec_pipe(ast, shell, w_splited, env);
        // printf("??????????????????????\n");
    }
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
