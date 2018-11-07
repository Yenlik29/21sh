/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 12:41:57 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/04 12:42:04 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				history_cursor_middle(t_shell *shell)
{
	int count;

	if (!(shell->history->prev))
		return ;
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	shell->position = shell->length;
	count = shell->length;
	while (count && shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		shell->position--;
		count--;
	}
	shell->history = shell->history->prev;
	print_line(shell);
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				history_down_cursor_end(t_shell *shell)
{
	int count;

	count = ft_strlen(shell->history->record);
	while (count)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		count--;
		shell->position--;
	}
	shell->history = shell->history->next;
	print_line(shell);
	shell->length = ft_strlen(shell->history->record);
	shell->position = ft_strlen(shell->history->record);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				history_down_cursor_middle(t_shell *shell)
{
	int count;

	if (!(shell->history->next))
		return ;
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	count = shell->length;
	while (count && shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		shell->position--;
		count--;
	}
	shell->history = shell->history->next;
	print_line(shell);
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				history_down(t_shell *shell)
{
	if (shell->history->next)
	{
		if (shell->position == shell->length)
			history_down_cursor_end(shell);
		else if (shell->position < shell->length)
			history_down_cursor_middle(shell);
	}
}
