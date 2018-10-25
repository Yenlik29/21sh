/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:11:02 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:11:03 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				ft_no_such_file_env_1(char *w_splited)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void				ft_permission_env(char *w_splited)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void				ft_no_such_file(char *w_splited)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putchar_fd('\n', 2);
}

void				ft_not_directory(char *w_splited)
{
	ft_putstr_fd("cd: not a directory: ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putchar_fd('\n', 2);
}

void				ft_permission_denied(char *w_splited)
{
	ft_putstr_fd("cd: permission denied: ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putchar_fd('\n', 2);
}
