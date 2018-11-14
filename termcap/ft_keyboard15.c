/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard15.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:59:00 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/13 19:59:00 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				multi_shift_left(t_shell *shell)
{
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (shell->position - sz.ws_col >= 0)
	{
		shell->position = shell->position - sz.ws_col;
		tputs(tgetstr("up", NULL), 1, re_putchar);
	}
	else
		home_key(shell);
}
