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
	size_t count;

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
	char *tmp;
	char *hey;

	hey = (char *)malloc(sizeof(char) * 2048);
	hey[0] = ch;
	tmp = ft_strdup(shell->history->record);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, hey, ft_strlen(hey));
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	set_cursor(shell);
	while (--shell->length)
		tputs(tgetstr("nd", NULL), 1, re_putchar);
	left_n_clean_shell(shell);
	set_cursor(shell);
	print_line(shell);
	while (shell->position != 1)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	free(tmp);
	free(hey);
}

void				add_history_line(t_shell *shell, uint64_t ch)
{
	if (shell->position == 0)
		begin_history_add(shell, ch);
	else if (shell->position > 0 && shell->position < shell->length)
		middle_history_add(shell, ch);
	else if (shell->position == shell->length)
		end_history_add(shell, ch);
	// printf("\n[%s]\n", shell->history->record);
	// printf("\n[%d]\n", shell->position);
	// printf("\n[%d]\n", shell->length);
	ch = 0;
}
