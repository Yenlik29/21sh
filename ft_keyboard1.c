/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:53:45 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/26 13:53:46 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				alt_left_key(t_shell *shell)
{
	if (shell->position)
	{
		if (ACT_CHAR == '\0' && PRE_CHAR > 32 && PRE_CHAR < 127)
			default_left_shift(shell);
		else if (C_CHAR && P_CHAR && A_CHAR)
			middle_left_shift(shell);
		else if (C_CHAR && PRE_CHAR == ' ' && AFT_CHAR == ' ')
			single_left_shift(shell);
		else if (C_CHAR && PRE_CHAR == ' ')
			begin_left_shift(shell);
		else if (ACT_CHAR == ' ' && P_CHAR && A_CHAR)
			begin_left_shift(shell);
		else if (ACT_CHAR == ' ')
			top_left_shift(shell);
		else if (ACT_CHAR == '\0')
			begin_left_shift(shell);
		else if (C_CHAR && P_CHAR)
			middle_left_shift(shell);
	}
}

void				symbol_del(t_shell *shell)
{
	if (shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		shell = symbol_remove(shell);
		shell->length--;
		shell->position--;
	}
}

void				enter_ch(t_shell *shell, uint64_t ch)
{
	if (shell->position == 0 && shell->length)
		begin_cursor(shell, ch);
	else if (shell->position > 0 && shell->position < shell->length)
		middle_cursor(shell, ch);
	else
	{
		shell->unparsed_com[shell->length] = ch;
		write(0, &(shell->unparsed_com[shell->length]), 1);
		shell->length++;
		shell->position++;
	}
}

void 				left_key(t_shell *shell)
{
	if (shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		(shell->position)--;
	}
}

void 				right_key(t_shell *shell)
{
	if (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
}

