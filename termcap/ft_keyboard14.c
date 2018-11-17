/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard14.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:44:02 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/13 19:44:03 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				multi_end_key(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	(R_L) ? out_line_right(shell) : default_right_shift(shell);
}

void				norm_end_key(t_shell *shell)
{
	tputs(tgetstr("nd", NULL), 1, re_putchar);
	shell->position++;
}

void				multi_home_key(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	// shell->position++;
	while (shell->position != -1)
	{
		row = row_find(row, shell);
		if (R_L)
			go_up(shell, sz);
		else
			in_line_left(shell);
		// printf("[%d,%d->%d]\n", shell->position + 5, row, ((sz.ws_col * (row - 1)) + 1));
		// exit(0);
	}
	shell->position = 0;
}

void				norm_home_key(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	while (shell->position)
	{
		if (shell->position + 4 == ((sz.ws_col * row) + 1))
		{
			go_up(shell, sz);
		}
		else
		{
			tputs(tgetstr("le", NULL), 1, re_putchar);
			shell->position--;
		}
	}
}
