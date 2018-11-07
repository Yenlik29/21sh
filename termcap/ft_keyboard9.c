/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:03:36 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/07 15:03:44 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				end_key(t_shell *shell)
{
	if (shell->position == shell->length)
		return ;
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
}

void				home_key(t_shell *shell)
{
	if (shell->position == 0)
		return ;
	else if (shell->position <= shell->length)
	{
		while (shell->position)
		{
			tputs(tgetstr("le", NULL), 1, re_putchar);
			shell->position--;
		}
	}
}
