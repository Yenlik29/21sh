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
	shell->history->record[shell->length] = ch;
	shell->history->record[shell->length + 1] = '\0';
	write(0, &(shell->history->record[shell->length]), 1);
	shell->length = ft_strlen(shell->history->record);
	shell->position++;
}