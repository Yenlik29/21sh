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

void				history_down(t_shell *shell)
{
	int count;

	// printf("[%s->%s]\n", shell->history->record, shell->history->next->record);
	// if (!(shell->history->next))
	if (shell->history->next)
	{
		// printf("[%s:%s]\n", shell->unparsed_com, shell->history->record);
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
	}
	// else
	// {
	// 	printf("!\n");
	// }
}
