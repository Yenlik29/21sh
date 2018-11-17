/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 10:45:49 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/04 10:45:57 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				in_line_left(t_shell *shell)
{
	tputs(tgetstr("le", NULL), 1, re_putchar);
	shell->position--;
}

void				out_line_left(t_shell *shell)
{
	int position;
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	position = shell->position - sz.ws_col;
	tputs(tgetstr("up", NULL), 1, re_putchar);
	shell->position--;
	while (position != shell->position)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		position++;
	}
}

void				clear_till_begin(t_shell *shell)
{
	while (shell->position--)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
	}
}

void				put_cursor(t_shell *shell)
{
	int len;
	int position;

	len = shell->length;
	position = shell->position;
	while (len != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		len--;
	}
	tputs(tgetstr("nd", NULL), 1, re_putchar);
	shell->position++;
}

void				end_history_add(t_shell *shell, uint64_t ch)
{
	int 			row;
	struct winsize sz;

	row = 0;
	row = row_find(row, shell);
	ioctl(0, TIOCGWINSZ, &sz);
	shell->history->record[shell->length] = ch;
	shell->history->record[shell->length + 1] = '\0';
	write(0, &(shell->history->record[shell->length]), 1);
	if (R_L)
		out_line_right(shell);
	else
		shell->position++;
	shell->length = ft_strlen(shell->history->record);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}
