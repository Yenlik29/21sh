/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:17:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/16 18:05:14 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                    pipeline(t_ast *left, t_ast *right)
{
    pid_t   pid;
    int     pfd[2];

    if (pipe(pfd) < 0)
        pipe_fd_error();
    pid = fork();
    // printf("[%s->%s]\n", left->tokens->info, right->tokens->info);
    left = NULL;
    right = NULL;
}

void                    exec_pipe(t_ast *ast, t_shell *shell, char **w_splited)
{
    if (!ast->left)
    {
        pipeline(ast, ast->parent->right);
        return ;
    }
    exec_pipe(ast->left, shell, w_splited);
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
        exec_pipe(ast, shell, w_splited);
    else if (ast->type != T_PIPE && ast->type != T_SEMI)
    {
        w_splited = array_assign(ast, w_splited);
        w_splited = parsed_word(w_splited, env);
        /* Сегфолт в parsed_word - посмотри как он обрабатывает переменные */
        // int l = 0;
        // while (w_splited[l])
        // {
        //     printf("\n[%s]\n", w_splited[l]);
        //     l++;
        // }
        // if (w_splited[0] != NULL)
        //     env = ft_core(w_splited, env);
        // if (w_splited)
        //     free_2darray(&w_splited);
    }
    return (env);
    // printf("?\n");
}
