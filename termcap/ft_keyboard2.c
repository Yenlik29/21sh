/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:49 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/26 22:54:50 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				go_cursor_end(t_shell *shell)
{
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
}

void				symbol_middle_remove(t_shell *shell)
{
	char *begin;
	char *end;
	int  position;

	position = shell->position - 1;
	begin = ft_strsub(shell->unparsed_com, 0, shell->position -1);
	end = ft_strsub(shell->unparsed_com, shell->position, shell->length - shell->position);
	go_cursor_end(shell);
	clear_till_begin(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, begin, ft_strlen(begin));
	ft_strncat(shell->history->record, end, ft_strlen(end));
	print_line(shell);
	set_cursor(shell);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
	free(begin);
	free(end);
}

t_shell				*symbol_remove(t_shell *shell)
{
	int 	i;
	char 	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(tmp);
	while (i < shell->length - 1)
	{
		tmp[i] = shell->unparsed_com[i];
		i++;
	}
	tmp[i] = '\0';
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	free(tmp);
	return (shell);
}

void				middle_cursor(t_shell *shell, uint64_t ch)
{
	char *tmp;
	char *begin;
	char *end;
	int  del;
	int  cursor;

	tmp = NULL;/////////////////////
	begin = NULL;/////////////////////////
	end = NULL;//////////////////////////////
	tmp = char_record(ch, tmp);
	begin = begin_record(begin, shell);
	del = ft_strlen(begin);
	ft_strncat(begin, tmp, ft_strlen(tmp));
	end = end_record(end, shell);
	cursor = ft_strlen(end);
	ft_strncat(begin, end, ft_strlen(end));
	shell = shell_set_settings(shell, begin);
	string_clear(shell, del);
	ft_putstr(shell->unparsed_com);
	while (cursor--)
		tputs(tgetstr("le", NULL), 1, re_putchar);
	free(tmp);
	free(begin);
	free(end);
}

void				begin_cursor(t_shell *shell, uint64_t ch)
{
	char *tmp;
	int  count;

	tmp = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(tmp);
	tmp = ft_strncat(tmp, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	ft_strclr(shell->unparsed_com);
	shell->unparsed_com[0] = ch;
	shell->unparsed_com = ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
	/////////
	// ft_strclr(shell->history->record);
	// ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->history->record));
	/////////
	count = shell->length;
	while (count--)
		tputs(tgetstr("dc", NULL), 1, re_putchar);
	shell->length = ft_strlen(shell->unparsed_com);
	ft_putstr(shell->unparsed_com);
	count = shell->length;
	while (--count)
		tputs(tgetstr("le", NULL), 1, re_putchar);
	shell->position = 1;
	free(tmp);
}