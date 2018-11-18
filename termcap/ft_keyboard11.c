/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard11.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:14:08 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/11 12:14:08 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			end_alt_left(t_shell *shell)
{
	in_line_left(shell);
	if (PRE_CHAR == ' ')
	{
		up_side(shell);
		while (ACT_CHAR == ' ' && shell->position)
			up_side(shell);
	}
	while (C_CHAR && shell->position)
	{
		if (PRE_CHAR == ' ')
			break ;
		up_side(shell);
	}
}

void			in_line_right(t_shell *shell)
{
	tputs(tgetstr("nd", NULL), 1, re_putchar);
	shell->position++;
}

void			out_line_right(t_shell *shell)
{
	int 			row;
	int 			position;
	struct winsize	sz;

	row = 0;
	row = row_find(row, shell);
	ioctl(0, TIOCGWINSZ, &sz);
	position = shell->position + sz.ws_col;
	shell->position++;
	while (position != shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		position--;
	}
	tputs(tgetstr("do", NULL), 1, re_putchar);
}

void			multi_right(t_shell *shell)
{
	int				row;
	struct winsize	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	if (shell->position + 4 == sz.ws_col * row)
		out_line_right(shell);
	else
		in_line_right(shell);
}

void			norm_edition(t_shell *shell, uint64_t ch)
{
	if (shell->position == 0 && shell->length)
		begin_cursor(shell, ch);
	else if (shell->position > 0 && shell->position < shell->length)
		middle_cursor(shell, ch);
	else
	{
		shell->unparsed_com[shell->length] = ch;
		shell->unparsed_com[shell->length + 1] = '\0';
		write(0, &(shell->unparsed_com[shell->length]), 1);
		shell->length = ft_strlen(shell->unparsed_com);
		shell->position++;
		ft_strclr(shell->history->record);
		ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	}
}
