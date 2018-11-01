/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:05:13 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/01 20:05:24 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				default_left_shift(t_shell *shell)
{
	tputs(tgetstr("le", NULL), 1, re_putchar);
	MINUS_POS;
	while (PRE_CHAR > 32 && PRE_CHAR < 127)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
}

void				middle_left_shift(t_shell *shell)
{
	while (PRE_CHAR > 32 && PRE_CHAR < 127)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		MINUS_POS;
	}
}

void				begin_left_shift(t_shell *shell)
{
	tputs(tgetstr("le", NULL), 1, re_putchar);
	MINUS_POS;
	middle_left_shift(shell);
}


