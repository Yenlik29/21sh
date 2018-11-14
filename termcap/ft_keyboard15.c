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

void				multi_shift_right(t_shell *shell)
{
	int 			count;
	int				row;
	int 			position;
	struct winsize 	sz;

	row = 0;
	row = row_find(row, shell);
	ioctl(0, TIOCGWINSZ, &sz);
	if (shell->position + sz.ws_col <= shell->length)
	{
		position = (row * sz.ws_col) - (shell->position + 3);
		position = sz.ws_col - position;
		tputs(tgetstr("do", NULL), 1, re_putchar);
		count = 0;
		while (count != position)
		{
			tputs(tgetstr("nd", NULL), 1, re_putchar);
			count++;
		}
		shell->position = shell->position + sz.ws_col;
		// printf("\n[%d->%d->%d]\n", shell->length + 3, shell->position + 3, sz.ws_col);
		// shell->position = shell->position + sz.ws_col;
	}
	else
		end_key(shell);
}

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
