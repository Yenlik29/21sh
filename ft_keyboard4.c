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

void				word_left_shift(t_shell *shell)
{
	while (ACT_CHAR > 32 && ACT_CHAR < 127)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
	while (ACT_CHAR == ' ' && shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
	while (C_CHAR)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
}

void				alt_right_key(t_shell *shell)
{
	if (shell->position != shell->length)
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
}