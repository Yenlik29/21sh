/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:52:31 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/21 14:52:31 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				print_inverse(t_shell *shell, int position)
{
	int 			count;

	count = 0;
	while (count < position)
	{
		write(0, &shell->history->record[count], 1);
		count++;
	}
	tputs(tgetstr("mr", NULL), 1, re_putchar);
	write(0, &shell->history->record[position], 1);
	tputs(tgetstr("me", NULL), 1, re_putchar);
	position++;
	count = position;
	while (position <= shell->length)
	{
		write(0, &shell->history->record[position], 1);
		position++;
	}
	while (position > count + 1)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		position--;
	}
	shell->position = count;
	// printf("[%d]\n", count);
}

void				right_selection(t_shell *shell)
{
	int position;
	char *tmp;

	tmp = ft_strdup(shell->history->record);
	position = shell->position;
	end_key(shell);
	set_cursor(shell);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	shell->length = ft_strlen(shell->history->record);
	// print_line
	print_inverse(shell, position);
}

void				left_selection(t_shell *shell)
{
	// tputs(tgetstr("le", NULL), 1, re_putchar);
	printf("Left selection\n");
	shell = NULL;
}
