/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:18:06 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/25 15:18:06 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			ft_error_tcgetattr(void)
{
	ft_putstr_fd("tcgetattr() error\n", 2);
}

void			ft_error_termdef(char *termtype)
{
	ft_putstr_fd("Terminal type ", 2);
	ft_putstr_fd(termtype, 2);
	ft_putstr_fd("is not defined.\n", 2);
}

void			ft_error_term_access(void)
{
	ft_putstr_fd("Could not access the termcap database.\n", 2);
}

void			ft_error_noterm(void)
{
	ft_putstr_fd("Specify a terminal type with `setenv TERM <yourtype>`.\n", 2);
}

void			ft_error_isatty(void)
{
	ft_putstr_fd("isatty() error\n", 2);
}