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
	while (shell->position >= shell->start && shell->position <= shell->end)
	{
		tputs(tgetstr("mr", NULL), 1, re_putchar);
		write(0, &shell->history->record[shell->position], 1);
		tputs(tgetstr("me", NULL), 1, re_putchar);
		shell->buf[ft_strlen(shell->buf)] = shell->history->record[shell->position];
		shell->buf[ft_strlen(shell->buf)] = '\0';
		shell->position++;
	}
	while (shell->position <= shell->length)
	{
		write(0, &shell->history->record[shell->position], 1);
		shell->position++;
	}
	position++;
	set_cursor(shell);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
}

void				right_selection(t_shell *shell)
{
	int position;
	char *tmp;

	if (shell->position == shell->length)
		return ;
	if (shell->start == 0)
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
}

void				left_selection(t_shell *shell)
{
	// tputs(tgetstr("le", NULL), 1, re_putchar);
	printf("Left selection\n");
	shell = NULL;
}