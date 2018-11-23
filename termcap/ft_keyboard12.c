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

	position = sz.ws_col - 1;
	tputs(tgetstr("up", NULL), 1, re_putchar);
	while (position)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		position--;
	}
	shell->position--;
}

void				space_alt_left(t_shell *shell)
{
	while (ACT_CHAR == ' ' && shell->position)
		up_side(shell);
	while (C_CHAR && shell->position)
	{
		if (PRE_CHAR == ' ')
			break ;
		up_side(shell);
	}
}

void				default_alt_left(t_shell *shell)
{
	if (PRE_CHAR == ' ')
	{
		up_side(shell);
		while (ACT_CHAR == ' ' && shell->position)
			up_side(shell);
	}
	while (C_CHAR && shell->position)
	{
		up_side(shell);
		if (PRE_CHAR == ' ')
			break ;
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
