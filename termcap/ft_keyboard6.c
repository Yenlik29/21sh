/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 09:52:13 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/04 09:52:22 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				print_line(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;
	size_t 			count;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	count = 0;
	while (count < ft_strlen(shell->history->record))
	{
		write(0, &shell->history->record[count], 1);
		count++;
	}
}

void				set_cursor(t_shell *shell)
{
	shell->length = ft_strlen(shell->history->record);
	shell->position = ft_strlen(shell->history->record);
}

void				left_n_clean_shell(t_shell *shell)
{
	while (shell->position != 1)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		shell->position--;
	}
}

void				begin_history_add(t_shell *shell, uint64_t ch)
{
	if (check_cursor(shell) == 0)
	{
		multi_begin_history_add(shell, ch);}
	else
	{
		// printf("*\n");
		norm_begin_history_add(shell, ch);}
}

void				add_history_line(t_shell *shell, uint64_t ch)
{
	if (shell->position == 0)
	{
		// printf("*\n");
		begin_history_add(shell, ch);
	}
	else if (shell->position > 0 && shell->position < shell->length)
	{
		// printf("!\n");
		middle_history_add(shell, ch);}
	else if (shell->position == shell->length)
	{
		// printf("+\n");
		end_history_add(shell, ch);
	}
}
