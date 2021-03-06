/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 10:26:05 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/04 10:26:11 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				place_cursor(t_shell *shell)
{
	int position;

	position = shell->position;
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->position = position;
	shell->length = ft_strlen(shell->history->record);
}

char 				*find_history_end(char *end, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < shell->position)
		i++;
	while (shell->history->record[i])
	{
		end[j] = shell->history->record[i];
		j++;
		i++;
	}
	end[j] = '\0';
	return (end);
}

char 				*end_history_record(char *end, t_shell *shell)
{
	// printf("*\n");
	end = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(end);
	end = find_history_end(end, shell);
	return (end);
}

char 				*begin_history_record(char *begin, t_shell *shell)
{
	begin = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(begin);
	ft_strncat(begin, shell->history->record, shell->position);
	return (begin);
}

void				middle_history_add(t_shell *shell, uint64_t ch)
{
	char *begin;
	char *end;
	char *tmp;
	char *ch_t;
	int position;
	struct winsize sz;

	ioctl(0, TIOCGWINSZ, &sz);
	ch_t = (char *)malloc(sizeof(char) * 2048);
	ch_t[0] = ch;
	ch_t[1] = '\0';
	end = NULL;
	begin = NULL;
	position = shell->position + 1;
	begin = begin_history_record(begin, shell);
	end = end_history_record(end, shell);
	tmp = ft_strncat(begin, ch_t, ft_strlen(ch_t));
	tmp = ft_strncat(tmp, end, ft_strlen(end));
	while (shell->position != shell->length)
		multi_end_key(shell);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	print_line(shell);
	set_cursor(shell);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	if ((shell->length + 3) % sz.ws_col == 0)
		tputs(tgetstr("nd", NULL), 1, re_putchar);
	shell->position = position;
	shell->length = ft_strlen(shell->history->record);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}
