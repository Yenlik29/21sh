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

void				selection(t_shell *shell)
{
	int end;
	int start;

	end = shell->end;
	start = shell->start;
	while (start != end)
	{
		tputs(tgetstr("mr", NULL), 1, re_putchar);
		write(0, &shell->history->record[shell->position], 1);
		shell->position++;
		start--;
	}
	tputs(tgetstr("me", NULL), 1, re_putchar);
	while (shell->position != shell->length)
	{
		write(0, &shell->history->record[shell->position], 1);
		shell->position++;
	}
}

void				shift_right_end(t_shell *shell)
{
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->history = shell->history->next;
	print_line(shell);
	set_cursor(shell);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
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
	shell->history = shell->history->next;
	print_line(shell);
	set_cursor(shell);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				shift_right(t_shell *shell)
{
	if (check_cursor(shell) == 0)
		multi_shift_right(shell);
	else
	{
		if (!(shell->history->next))
			return ;
		if (shell->position > (int)ft_strlen(shell->history->next->record))
			shift_right_end(shell);
		else
			shift_right_norm(shell);
	}
	shell->start = 0;
	shell->end = 0;
}
