/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:17:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/15 13:46:41 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                    exec_semi(t_ast *ast, t_shell *shell, char **env, char **w_splited)
{
    execution(ast->left, shell, env, w_splited);
    // printf("!\n");
    execution(ast->right, shell, env, w_splited);
    // printf("!\n");
}

void                    execution(t_ast *ast, t_shell *shell, char **env, char **w_splited)
{
    if (!ast)
        return ;
    else if (ast->type == T_SEMI)
        exec_semi(ast, shell, env, w_splited);
    else if (ast->type == T_PIPE)
        printf("PIPE!\n");
    else if (ast->type != T_PIPE && ast->type != T_SEMI)
    {
        w_splited = split_word(ast->tokens->info);
        w_splited = parsed_word(w_splited, env);
        if (w_splited[0] != NULL)
            env = ft_core(w_splited, env);
    }
    // printf("?\n");
}
