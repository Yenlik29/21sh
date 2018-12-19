/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_src3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:35:38 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/19 20:20:40 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                check_create_existance(char *name, int type)
{
    int fd;
    // write(0, ft_itoa(type), ft_strlen(ft_itoa(type)));
    // name = NULL;
    if (access(name, F_OK) != -1 /* ПРОВЕРЬ НА ДИРЕКТОРИЮ !!! */)
    {
        write(0, "exist\n", ft_strlen("exist\n"));
    }
    else if (access(name, F_OK) != -1)
    {
        /* Тут права другие дожны быть для редайрекций, ЧЕКНИ !!! */
        if (((access(name, W_OK) == 0) && (access(name, R_OK) != 0)
		&& (access(name, X_OK) != 0)) || ((access(name, W_OK) != 0)
		&& (access(name, R_OK) == 0) && (access(name, X_OK) != 0)) ||
		((access(name, W_OK) == 0) && (access(name, R_OK) == 0)
		&& (access(name, X_OK) != 0)) || ((access(name, W_OK) != 0)
		&& (access(name, R_OK) != 0) && (access(name, X_OK) != 0)))
        {
            ft_permission_denied(name);
            // return (0);
        }
    }
    else if ((fd = open(name, O_DIRECTORY)) != -1)
		is_a_directory(name);
    else
    {
        write(0, "don't exist\n", ft_strlen("don't exist\n"));
    }
    type = 0;
}

void                check_files(t_ast *ast)
{
    while (ast->tokens)
    {
        if (!ft_strcmp(ast->tokens->info, ">") || !ft_strcmp(ast->tokens->info, ">>"))
            check_create_existance(ast->tokens->next->info, ast->tokens->type);
        if (ast->tokens->next)
            ast->tokens = ast->tokens->next;
        else
            break ;
    }
}
