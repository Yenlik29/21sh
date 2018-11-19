/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:11:10 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:11:11 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				ft_not_set(char *word)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd(" not set\n", 2);
}

void				ft_not_in_cwd(char *w_splited)
{
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putchar_fd('\n', 2);
}

void				ft_setenv_parse_error(char *w_splited)
{
	ft_putstr_fd("un/setenv: parse error : ", 2);
	ft_putstr_fd(w_splited, 2);
	ft_putstr_fd(" \n", 2);
}

void				ft_setenv_arg_error(void)
{
	ft_putstr_fd("un/setenv: need to add arguments\n", 2);
}

void				ft_setenv_overload(void)
{
	ft_putstr_fd("un/setenv: too many arguments\n", 2);
}
