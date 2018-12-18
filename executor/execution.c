/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:17:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/18 14:20:18 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                    right_pipe(int fd[2], t_ast *right, char **env)
{
    pid_t pid;

    if ((pid = fork()) == -1)
        fork_error();
    if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        char **w_splited;
        w_splited = NULL;
        w_splited = array_assign(right, w_splited);
        w_splited = parsed_word(w_splited, env);
        // int l = 0;
        // while (w_splited[l])
        // {
        //     printf("[%s]\n", w_splited[l]);
        //     l++;
        // }
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
        char **w_splited;
        // t_ast *temp;

        // temp = left;
        w_splited = NULL;
        w_splited = array_assign(left, w_splited);
        w_splited = parsed_word(w_splited, env);
        if (check_redir(w_splited))
        {    redir_exec(w_splited, env, left);
            // exit(0);
        }
        else
            stand_exec(w_splited, env, fd);
        // int l = 0;
        // while (w_splited[l])
        // {
        //     write(0, "[", ft_strlen("["));
        //     write(0, w_splited[l], ft_strlen(w_splited[l]));
        //     write(0, "]\n", ft_strlen("]\n"));
        //     l++;
        // }
    }
    else
    {
        waitpid(pid, NULL, WUNTRACED);
        // right = NULL;
        right_pipe(fd, right, env);
    }
}

void                    exec_pipe(t_ast *ast, t_shell *shell, char **w_splited, char **env)
{
    if (!ast->left)
    {
        // while (ast->tokens)
        // {
        //     printf("[%s]\n", ast->tokens->info);
        //     if (ast->tokens->next)
        //         ast->tokens = ast->tokens->next;
        //     else
        //         break ;
        // }
        /* тут надо сделать парсинг на редайрекции !!! */
        pipeline(ast, ast->parent->right, env);
        // right = NULL;
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
        if (check_redir(w_splited))
            redir_exec(w_splited, env, ast);
        else
        {
            if (w_splited[0] != NULL)
                env = ft_core(w_splited, env);
            if (w_splited)
                free_2darray(&w_splited);
        }
    }
    return (env);
}
