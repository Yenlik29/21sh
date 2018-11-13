/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard12.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:03:24 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/13 15:03:26 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				go_up(t_shell *shell, struct winsize sz)
{
	int position;

	position = shell->position - sz.ws_col;
	shell->position--;
	tputs(tgetstr("up", NULL), 1, re_putchar);
	while (position != shell->position)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		position++;
	}
}

void				space_alt_left(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	while (ACT_CHAR == ' ' && shell->position)
		(L_L) ? go_up(shell, sz) : in_line_left(shell);
	while (C_CHAR && shell->position)
	{
		if (PRE_CHAR == ' ')
			break ;
		(L_L) ? go_up(shell, sz) : in_line_left(shell);
	}
}

void				default_alt_left(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	if (PRE_CHAR == ' ')
	{
		(L_L) ? go_up(shell, sz) : in_line_left(shell);
		while (ACT_CHAR == ' ' && shell->position)
			(L_L) ? go_up(shell, sz) : in_line_left(shell);
	}
	while (C_CHAR && shell->position)
	{
		if (PRE_CHAR == ' ')
			break ;
		(L_L) ? go_up(shell, sz) : in_line_left(shell);
	}
}

void				multi_alt_left(t_shell *shell)
{
	if (C_CHAR)
		default_alt_left(shell);
	else if (ACT_CHAR == ' ')
		space_alt_left(shell);
	else if (ACT_CHAR == '\0')
		end_alt_left(shell);
}

void				norm_alt_left(t_shell *shell)
{
	if (ACT_CHAR == '\0' && PRE_CHAR > 32 && PRE_CHAR < 127)
		default_left_shift(shell);
	else if (C_CHAR && P_CHAR && A_CHAR)
		middle_left_shift(shell);
	else if (C_CHAR && PRE_CHAR == ' ' && AFT_CHAR == ' ')
		single_left_shift(shell);
	else if (C_CHAR && PRE_CHAR == ' ' && A_CHAR)
		word_left_shift(shell);
	else if (C_CHAR && PRE_CHAR == ' ' && AFT_CHAR == '\0')
		single_left_shift(shell);
	else if (ACT_CHAR == ' ' && P_CHAR && A_CHAR)
		begin_left_shift(shell);
	else if (ACT_CHAR == ' ')
		top_left_shift(shell);
	else if (ACT_CHAR == '\0')
		begin_left_shift(shell);
	else if (C_CHAR && P_CHAR)
		middle_left_shift(shell);
}
