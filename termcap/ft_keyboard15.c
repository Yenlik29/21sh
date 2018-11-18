/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard15.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:59:00 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/13 19:59:00 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				up_side(t_shell *shell)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	row = row_find(row, shell);
	if (R_L)
	{
		go_up(shell, sz);
		tputs(tgetstr("le", NULL), 1, re_putchar);
	}
	else
		in_line_left(shell);
}

void				multi_begin_history_add(t_shell *shell, uint64_t ch)
{
	char *tmp;
	char *hey;
	struct winsize 	sz;

	ioctl(0, TIOCGWINSZ, &sz);
	hey = (char *)malloc(sizeof(char) * 2048);
	hey[0] = ch;
	hey[1] = '\0';
	tmp = ft_strdup(shell->history->record);
	end_key(shell);
	set_cursor(shell);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, hey, ft_strlen(hey));
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	print_line(shell);
	set_cursor(shell);
	while (shell->position != 1)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	if ((shell->length + 3) % sz.ws_col == 0)
		tputs(tgetstr("nd", NULL), 1, re_putchar);
	shell->position = 1;
	shell->length = ft_strlen(shell->history->record);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
	free(tmp);
	free(hey);
}

void				norm_begin_history_add(t_shell *shell, uint64_t ch)
{
	char *tmp;
	char *hey;
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	hey = (char *)malloc(sizeof(char) * 2048);
	hey[0] = ch;
	hey[1] = '\0';
	tmp = ft_strdup(shell->history->record);
	while (shell->position != shell->length)
		multi_end_key(shell);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, hey, ft_strlen(hey));
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	print_line(shell);
	set_cursor(shell);
	while (shell->position != 1)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	if ((shell->length + 3) % sz.ws_col == 0)
		tputs(tgetstr("nd", NULL), 1, re_putchar);
	shell->position = 1;
	shell->length = ft_strlen(shell->history->record);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
	free(tmp);
	free(hey);
}

void				multi_shift_right(t_shell *shell)
{
	int 			count;
	int				row;
	int 			position;
	struct winsize 	sz;

	row = 0;
	row = row_find(row, shell);
	ioctl(0, TIOCGWINSZ, &sz);
	if (shell->position + sz.ws_col <= shell->length)
	{
		position = (row * sz.ws_col) - (shell->position + 3);
		position = sz.ws_col - position;
		tputs(tgetstr("do", NULL), 1, re_putchar);
		count = 0;
		while (count != position)
		{
			tputs(tgetstr("nd", NULL), 1, re_putchar);
			count++;
		}
		shell->position = shell->position + sz.ws_col;
	}
}

void				multi_shift_left(t_shell *shell)
{
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (shell->position - sz.ws_col >= 0)
	{
		shell->position = shell->position - sz.ws_col;
		tputs(tgetstr("up", NULL), 1, re_putchar);
	}
}
