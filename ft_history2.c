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
	int position;

	if (shell->history->next)
	{
		shell->history = shell->history->next;
		position = shell->position;
		while (position--)
		{
			tputs(tgetstr("le", NULL), 1, re_putchar);
			tputs(tgetstr("dc", NULL), 1, re_putchar);
			shell->position--;
		}
		print_line(shell);
	}
}