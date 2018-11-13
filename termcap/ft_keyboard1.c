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

void				alt_left_key(t_shell *shell)
{
	if (shell->position)
	{
		if (check_cursor(shell) == 0)
			multi_alt_left(shell);
		else
			norm_alt_left(shell);
	}
}

void				symbol_del(t_shell *shell)
{
	if (shell->position)
	{
		if (shell->position == shell->length)
		{
			tputs(tgetstr("le", NULL), 1, re_putchar);
			tputs(tgetstr("dc", NULL), 1, re_putchar);
			shell = symbol_remove(shell);
			shell->length--;
			shell->position--;
		}
		else
			symbol_middle_remove(shell);
	}
}

void				enter_ch(t_shell *shell, uint64_t ch)
{
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (shell->history->record[0])
	{
		// if (shell->length + 4 > sz.ws_col)
		// 	printf("AU\n");
		// else
			add_history_line(shell, ch);}
	else
	{
		// if (shell->length + 4 > sz.ws_col)
		// {
		// 	printf("AU\n");
		// }
		// else
			norm_edition(shell, ch);
	}
	// printf("[%d->%d]\n", sz.ws_col, shell->length + 3);
}

void 				left_key(t_shell *shell)
{
	if (shell->position)
	{
		if (check_cursor(shell) == 0)
			multi_left(shell);
		else
		{
			tputs(tgetstr("le", NULL), 1, re_putchar);
			(shell->position)--;
		}
	}
}

void 				right_key(t_shell *shell)
{
	if (shell->position != shell->length)
	{
		if (check_cursor(shell) == 0)
			multi_right(shell);
		else
		{
			tputs(tgetstr("nd", NULL), 1, re_putchar);
			shell->position++;
		}
	}
}

