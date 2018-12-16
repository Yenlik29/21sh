/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_src.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:22:14 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/16 18:00:47 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char                **array_assign(t_ast *ast, char **w_splited)
{
    int i;

    i = 0;
    if (!(w_splited = (char **)malloc(sizeof(char) * 2048)))
        return (NULL);
    while (ast->tokens && ast->tokens->info[0])
    {
        if (!(w_splited[i] = (char *)malloc(sizeof(char) * 2048)))
            return (NULL);
        ft_strclr(w_splited[i]);
        ft_strncpy(w_splited[i], ast->tokens->info, ft_strlen(ast->tokens->info));
        // printf("[%s]\n", w_splited[i]);
        if (ast->tokens->next)
            ast->tokens = ast->tokens->next;
        else
            return (w_splited);
        i++;
    }
    // w_splited[i] = NULL;
    return (w_splited);
}
