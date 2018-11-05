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

void				history_up(t_shell *shell)
{
	int count;
	char *tmp;

	if (!(shell->history->prev))
		return ;
	if (shell->history->record[0])
	{
		// shell->position = 0;
		tmp = ft_strdup(shell->history->record);
		ft_strclr(shell->history->record);
		ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
		count = ft_strlen(shell->history->record);
		while (count--)
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
		// shell->position = ft_strlen(shell->history->record);
		shell->length = ft_strlen(shell->history->record);
		// printf("[%d:%d]\n", shell->position, shell->length);
	}
	else
	{
		ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
		count = ft_strlen(shell->history->record);
		while (count--)
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
	}
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
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	new_node->next = NULL;
	return (shell);
}
