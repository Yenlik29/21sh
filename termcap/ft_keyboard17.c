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

void				print_left_inverse(t_shell *shell, int position)
{
	while (shell->start != shell->end)
	{
		tputs(tgetstr("mr", NULL), 1, re_putchar);
		write(0, &shell->history->record[shell->position], 1);
		shell->position--;
		shell->start--;
	}
	tputs(tgetstr("me", NULL), 1, re_putchar);
	position = 0;
}

void				left_default_selection(t_shell *shell, char *tmp)
{
	if (!shell->position)
		return ;
	if (!shell->start && !shell->end)
	{
		shell->start = shell->position;
		shell->end = shell->position;
	}
	left_inverse_selection(shell, tmp);
}

char				*cutted_buf_creation(t_shell *shell, char *new, int *cursor)
{
	int i;
	int position;

	i = 0;
	position = shell->end;
	*cursor = shell->start;
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

char 				*reversed_buf_create(t_shell *shell, char *new, int *cursor)
{
	int i;
	int position;
	
	i = 0;
	position = shell->start;
	*cursor = shell->end;
	new = (char *)malloc(sizeof(char) * 2048);
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
	if (shell->start <= shell->end)
		new = cutted_buf_creation(shell, new, &position);
	if (shell->start > shell->end)
		new = reversed_buf_create(shell, new, &position);
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








