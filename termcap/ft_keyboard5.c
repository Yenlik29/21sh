/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:04:45 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/02 13:04:52 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				default_right_shift(t_shell *shell)
{
	tputs(tgetstr("nd", NULL), 1, re_putchar);
	PLUS_POS;
}

void				middle_right_shift(t_shell *shell)
{
	while (ACT_CHAR > 32 && ACT_CHAR < 127)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		PLUS_POS;
	}
	while (ACT_CHAR == ' ')
		default_right_shift(shell);
}

void				next_char_right_shift(t_shell *shell)
{
	while (ACT_CHAR > 32 && ACT_CHAR < 127)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		PLUS_POS;
	}
	while (ACT_CHAR == ' ')
		default_right_shift(shell);
	if (ACT_CHAR == '\0')
		return ;
}

void				till_char_right_shift(t_shell *shell)
{
	while (ACT_CHAR >= 32 && ACT_CHAR < 127)
	{
		if (ACT_CHAR == '\0')
			break ;
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		PLUS_POS;
	}
}

void				char_right_shift(t_shell *shell)
{
	while (ACT_CHAR == ' ')
		default_right_shift(shell);
}
