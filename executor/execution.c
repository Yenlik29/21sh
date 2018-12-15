/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:17:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/15 13:55:12 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                    exec_pipe(t_ast *ast, t_shell *shell, char **w_splited)
{
    printf("heey PIPE!\n");
    ast = NULL;
    shell = NULL;
    w_splited = NULL;
    // if (!ast->left)
    //     pipeline(ast, ast->parent->right);
    // exec_pipe(ast->left, shell, w_splited);
}

void                    exec_semi(t_ast *ast, t_shell *shell, char **env, char **w_splited)
{
    execution(ast->left, shell, env, w_splited);
    execution(ast->right, shell, env, w_splited);
}

void                    execution(t_ast *ast, t_shell *shell, char **env, char **w_splited)
{
    if (!ast)
        return ;
    else if (ast->type == T_SEMI)
        exec_semi(ast, shell, env, w_splited);
    else if (ast->type == T_PIPE)
        exec_pipe(ast, shell, w_splited);
    else if (ast->type != T_PIPE && ast->type != T_SEMI)
    {
        w_splited = split_word(ast->tokens->info);
        w_splited = parsed_word(w_splited, env);
        if (w_splited[0] != NULL)
            env = ft_core(w_splited, env);
    }
    // printf("?\n");
}
