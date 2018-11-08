/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 12:14:40 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/03 12:14:42 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				history_cursor_edition(t_shell *shell)
{
	int count;

	count = ft_strlen(shell->unparsed_com);
	// printf("[%s->%s]\n", shell->unparsed_com, shell->history->record);
	while (count && shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		count--;
		shell->position--;
	}
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	shell->history = shell->history->prev;
	count = 0;
	while ((size_t)count < ft_strlen(shell->history->record))
	{
		write(0, &shell->history->record[count], 1);
		shell->position++;
		count++;
	}
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				history_cursor_done(t_shell *shell)
{
	int count;

	count = ft_strlen(shell->history->record);
	while (count-- && shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		tputs(tgetstr("dc", NULL), 1, re_putchar);
		shell->position--;
	}
	shell->history = shell->history->prev;
	count = 0;
	while ((size_t)count < ft_strlen(shell->history->record))
	{
		write(0, &shell->history->record[count], 1);
		shell->position++;
		count++;
	}
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				history_up(t_shell *shell)
{
	if (!(shell->history->prev))
		return ;
	if (shell->position < shell->length)
	{
		// printf("*\n");
		history_cursor_middle(shell);
	}
	else if (shell->unparsed_com[0])
	{
		// printf("!\n");
		history_cursor_edition(shell);
	}
	else if (shell->position == shell->length)
		history_cursor_done(shell);
}

void				new_history(t_shell *shell)
{
	if (!(shell->history->record = (char *)malloc(sizeof(char) * 2048)))
		return ;
	ft_strclr(shell->history->record);
	shell->history->next = NULL;
	shell->history->prev = NULL;
}

t_shell				*add_history(t_shell *shell)
{
	t_history	*tmp;
	t_history	*new_node;

	if (!(new_node = (t_history *)malloc(sizeof(t_history))))
		return (NULL);
	tmp = shell->history;
	if (shell->history == NULL)
	{
		shell->history = new_node;
		return (NULL);
	}
	new_node->record = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(new_node->record);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	new_node->next = NULL;
	return (shell);
}
