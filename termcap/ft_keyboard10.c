/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard10.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:29:22 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/07 16:29:33 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				shift_right_end(t_shell *shell)
{
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->position = 0;
	shell->history = shell->history->next;
	print_line(shell);
	set_cursor(shell);
}

void				shift_right_norm(t_shell *shell)
{
	int position;

	position = shell->position;
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->position = 0;
	shell->history = shell->history->next;
	print_line(shell);
	set_cursor(shell);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
}

void				shift_right(t_shell *shell)
{
	if (!(shell->history->next))
		return ;
	// printf("[%s->%s]\n", shell->unparsed_com, shell->history->next->record);
	if (shell->position > (int)ft_strlen(shell->history->next->record))
		shift_right_end(shell);
	else
		shift_right_norm(shell);
	// printf("[%d]\n", shell->position);
}
