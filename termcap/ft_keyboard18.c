/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard18.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:57:29 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/26 13:57:29 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				right_del_func(t_shell *shell, int position, char *tmp)
{
	end_key(shell);
	set_cursor(shell);
	while (shell->position != position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	shell->length = ft_strlen(shell->history->record);
	while (shell->position < shell->end)
	{
		tputs(tgetstr("me", NULL), 1, re_putchar);
		write(0, &shell->history->record[shell->position], 1);
		shell->position++;
	}
	position = shell->end;
	while (position < shell->start)
	{
		tputs(tgetstr("mr", NULL), 1, re_putchar);
		write(0, &shell->history->record[shell->position], 1);
		position++;
		shell->position++;
	}
}

void				print_n_cursor(t_shell *shell, int cursor)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	while (shell->position != shell->length)
	{
		write(0, &shell->history->record[shell->position], 1);
		shell->position++;
	}
	while (shell->position != cursor - 1)
	{
		row = row_find(row, shell);
		if (((sz.ws_col * (row - 1)) + 1) <= shell->position + 3 && shell->position + 3 <= (sz.ws_col * row))
			in_line_left(shell);
		else
			out_line_left(shell);
	}
}

void				right_inverse_selection(t_shell *shell)
{
	char *tmp;
	int cursor;
	int position;
	
	tmp = ft_strdup(shell->history->record);
	position = shell->end;
	shell->end++;
	buf_change_reverse(shell);
	cursor = shell->end;
	right_del_func(shell, position, tmp);
	tputs(tgetstr("me", NULL), 1, re_putchar);
	print_n_cursor(shell, cursor);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
	free(tmp);
}

void				default_right_selection(t_shell *shell)
{
	int position;
	char *tmp;

	if (shell->start == 0 && !shell->end)
	{
		shell->start = shell->position;
		shell->end = shell->position++;
		shell->position--;
	}
	tmp = ft_strdup(shell->history->record);
	position = shell->position;
	end_key(shell);
	set_cursor(shell);
	while (shell->position != position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	shell->length = ft_strlen(shell->history->record);
	print_inverse(shell, position);
	shell->end++;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
	free(tmp);
}
