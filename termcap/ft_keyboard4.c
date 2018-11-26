/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:34:59 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/01 20:35:07 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int 				row_find(int row, t_shell *shell)
{
	struct winsize 	sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (((shell->length + 3) % sz.ws_col) != 0)
		row = ((shell->length + 3) / sz.ws_col) + 1;
	else
		row = (shell->length + 3) / sz.ws_col;
	while (row)
	{
		if ((row - 1) * sz.ws_col <= shell->position + 3 && shell->position + 3 <= row *sz.ws_col)
			return (row);
		else
			row--;
	}
	return (row);
}

void				multi_left(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	if (((sz.ws_col * (row - 1)) + 1) <= shell->position + 3 && shell->position + 3 <= (sz.ws_col * row))
		in_line_left(shell);
	else
		out_line_left(shell);
}

int					check_cursor(t_shell *shell)
{
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (shell->length + 3 > sz.ws_col)
		return (0);
	else
		return (1);
}

void				word_left_shift(t_shell *shell)
{
	while (ACT_CHAR > 32 && ACT_CHAR < 127 && shell->position != 0)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
	while (ACT_CHAR == ' ' && shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
	while (C_CHAR && shell->position != 0)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
	if (ACT_CHAR == ' ' && shell->position != 0)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		PLUS_POS;
	}
}

void				alt_right_key(t_shell *shell)
{
	if (shell->position != shell->length)
	{
		if (check_cursor(shell) == 0)
			multi_alt_right(shell);
		else
			norm_alt_right(shell);
		shell->start = 0;
		shell->end = 0;
	}
}