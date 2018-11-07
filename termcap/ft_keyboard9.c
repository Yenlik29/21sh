/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:03:36 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/07 15:03:44 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				shift_left(t_shell *shell)
{
	int position;

	position = shell->position;
	if (!(shell->history->prev))
		return ;
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->history = shell->history->prev;
	print_line(shell);
	shell->position = ft_strlen(shell->history->record);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	// shell->position = ft_strlen;
	// printf("[%s|%s->%d:%d]\n", shell->unparsed_com, shell->history->record, shell->position, shell->length);
}

void				end_key(t_shell *shell)
{
	if (shell->position == shell->length)
		return ;
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
}

void				home_key(t_shell *shell)
{
	if (shell->position == 0)
		return ;
	else if (shell->position <= shell->length)
	{
		while (shell->position)
		{
			tputs(tgetstr("le", NULL), 1, re_putchar);
			shell->position--;
		}
	}
}
