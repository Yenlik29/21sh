/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard17.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:09:06 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/23 15:09:07 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char				*cutted_buf_creation(t_shell *shell, char *new)
{
	int i;
	int position;

	i = 0;
	position = shell->end;
	new = (char *)malloc(sizeof(char) * 2048);
	while (i < shell->start)
	{
		new[i] = shell->history->record[i];
		i++;
	}
	while (shell->end <= shell->length)
	{
		new[i] = shell->history->record[shell->end];
		i++;
		shell->end++;
	}
	new[i] = '\0';
	shell->end = position;
	return (new);
}

char 				*reversed_buf_create(t_shell *shell, char *new)
{
	int i;
	int position;
	
	i = 0;
	position = shell->start;
	while (i < shell->end)
	{
		new[i] = shell->history->record[i];
		i++;
	}
	while (shell->start <= shell->length)
	{
		new[i] = shell->history->record[shell->start];
		i++;
		shell->start++;
	}
	new[i] = '\0';
	shell->start = position;
	return (new);
}

void				cut(t_shell *shell)
{
	size_t i;
	char *new;
	int position;

	i = 0;
	new = NULL;
	position = shell->start;
	if (shell->start <= shell->end)
		new = cutted_buf_creation(shell, new);
	else if (shell->start > shell->end)
		new = reversed_buf_create(shell, new);
	end_key(shell);
	set_cursor(shell);
	while (shell->position)
		symbol_del(shell);
	set_cursor(shell);
	while (i <= ft_strlen(new))
	{
		write(0, &new[i], 1);
		i++;
	}
	shell->position = ft_strlen(new);
	shell->length = ft_strlen(new);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, new, ft_strlen(new));
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, new, ft_strlen(new));
	free(new);
}








