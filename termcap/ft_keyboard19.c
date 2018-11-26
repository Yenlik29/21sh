/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard19.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:36:10 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/26 21:36:11 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					copy(t_shell *shell)
{
	char *tmp;

	end_key(shell);
	set_cursor(shell);
	tmp = ft_strdup(shell->history->record);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	set_cursor(shell);
	ft_putstr(shell->history->record);
	free(tmp);
}

char					*end_paste(t_shell *shell, char *end)
{
	int i;
	int position;

	i = 0;
	position = shell->position;
	while (position <= shell->length)
	{
		end[i] = shell->history->record[position];
		i++;
		position++;
	}
	end[i] = '\0';
	return (end);
}

char					*begin_(t_shell *shell, int position, int *i, char *new)
{
	while (shell->position < position)
	{
		new[*i] = shell->history->record[shell->position];
		(*i)++;
		shell->position++;
	}
	return (new);
}

char					*new_pasted_string(t_shell *shell, char *new, int position, char *end)
{
	int i;
	int k;

	i = 0;
	k = 0;
	new = begin_(shell, position, &i, new);
	while (shell->buf[k])
	{
		new[i] = shell->buf[k];
		i++;
		k++;
	}
	k = 0;
	while (end[k])
	{
		new[i] = end[k];
		i++;
		k++;
	}
	new[i] = '\0';
	return (new);
}

void					cursor_alignment(t_shell *shell, int cursor)
{
	int 			row;
	struct winsize 	sz;

	row = 0;
	ioctl(0, TIOCGWINSZ, &sz);
	while (shell->position != cursor)
	{
		row = row_find(row, shell);
		if (((sz.ws_col * (row - 1)) + 1) <= shell->position + 3 && shell->position + 3 <= (sz.ws_col * row))
			in_line_left(shell);
		else
			out_line_left(shell);
	}
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void					paste(t_shell *shell)
{
	char *tmp;
	char *new;
	int position;
	char *end;
	int cursor;

	cursor = shell->position + ft_strlen(shell->buf);
	end = (char *)malloc(sizeof(char) * 2048);
	end = end_paste(shell, end);
	position = shell->position;
	end_key(shell);
	set_cursor(shell);
	new = (char *)malloc(sizeof(char) * 2048);
	tmp = ft_strdup(shell->history->record);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	new_pasted_string(shell, new, position, end);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, new, ft_strlen(new));
	ft_putstr(shell->history->record);
	set_cursor(shell);
	cursor_alignment(shell, cursor);
	free_3var(new, tmp, end);
}
