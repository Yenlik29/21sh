/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:56:01 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/25 14:56:02 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				re_putchar(int ch)
{
	return (write(0, &ch, 1));
}

int				terminal_init()
{
	char	*termtype;
	char	term_buf[2048];
	int		success;

	if (!(isatty(0)))
	{
		ft_error_isatty();
		return (-1);
	}
	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_error_noterm();
		exit(0);
	}
	success = tgetent(term_buf, termtype);
	(success < 0) ? ft_error_term_access() : NULL;
	(success == 0) ? ft_error_termdef(termtype) : NULL;
	return (success);
}

int				terminal_define(void)
{
	struct termios	original;
	struct termios	copy;

	if (tcgetattr(0, &original) != 0)
	{
		ft_error_tcgetattr();
		return (0);
	}
	else
	{
		copy = original;
		copy.c_lflag &= ~ICANON;
		if (tcsetattr(0, TCSANOW, &copy) != 0)
		{
			ft_error_tcsetattr();
			return (0);
		}
	}
	tputs(tgetstr("ti", NULL), 1, re_putchar);
	// tputs(tgetstr("vi", NULL), 1, re_putchar);
	return (1);
}
