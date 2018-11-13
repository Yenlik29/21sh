/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard13.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:09:04 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/13 19:09:04 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				default_alt_right(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	while (C_CHAR && shell->position != shell->length)
		(R_L) ? out_line_right(shell) : default_right_shift(shell);
	while (ACT_CHAR == ' ')
	{
		if (C_CHAR)
			break ;
		(R_L) ? out_line_right(shell) : default_right_shift(shell);
	}
}

void				space_alt_right(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	while (ACT_CHAR == ' ' && shell->position != shell->length)
		(R_L) ? out_line_right(shell) : default_right_shift(shell);
}

void				multi_alt_right(t_shell *shell)
{
	if (ACT_CHAR == ' ')
		space_alt_right(shell);
	else if (C_CHAR)
		default_alt_right(shell);
}

void				norm_alt_right(t_shell *shell)
{
	if (C_CHAR && AFT_CHAR == '\0')
		default_right_shift(shell);
	else if (C_CHAR && P_CHAR && A_CHAR)
		middle_right_shift(shell);
	else if (C_CHAR && PRE_CHAR == ' ' && A_CHAR)
		middle_right_shift(shell);
	else if (ACT_CHAR == ' ')
		char_right_shift(shell);
	else if (C_CHAR && AFT_CHAR == ' ' && PRE_CHAR == ' ')
		middle_right_shift(shell);
	else if (C_CHAR && AFT_CHAR == ' ')
		next_char_right_shift(shell);
	else if (C_CHAR && A_CHAR)
		next_char_right_shift(shell);
}
