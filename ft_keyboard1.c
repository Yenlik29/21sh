/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:53:45 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/26 13:53:46 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				symbol_del(t_shell *shell)
{
	int count;
	int del;

	count = shell->length;
	while (count--)
		tputs(tgetstr("dc", NULL), 1, re_putchar);
	// count = shell->length;
	// 	tputs(tgetstr("le", NULL), 1, re_putchar);
	// del = ft_strlen(shell->unparsed_com);
	// count = ft_strlen(shell->unparsed_com);
	// while (del--)
	// 	tputs(tgetstr("dc", NULL), 1, re_putchar);
	shell = symbol_remove(shell);
	// printf("[%d]\n", del);
	// while (count--)
	// 	tputs(tgetstr("le", NULL), 1, re_putchar);
	// printf("[%s]:[%d]\n", shell->unparsed_com, count);
	// printf("[%d]\n", del);
	// count = ft_strlen(shell->unparsed_com);
	// while (count--)
	// 	tputs(tgetstr("nd", NULL), 1, re_putchar);
	// ft_putstr(shell->unparsed_com);
	// tputs(tgetstr("rc", NULL), 0, re_putchar);
	shell->length = ft_strlen(shell->unparsed_com);
	shell->position = ft_strlen(shell->unparsed_com);
}

void				enter_ch(t_shell *shell, uint64_t ch)
{
	if (shell->position == 0 && shell->length)
		begin_cursor(shell, ch);
	else if (shell->position > 0 && shell->position < shell->length)
		middle_cursor(shell, ch);
	else
	{
		shell->unparsed_com[shell->length] = ch;
		write(0, &(shell->unparsed_com[shell->length]), 1);
		shell->length++;
		shell->position++;
	}
}

void 				left_key(t_shell *shell)
{
	if (shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		(shell->position)--;
	}
}

void 				right_key(t_shell *shell)
{
	if (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
}

