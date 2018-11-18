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
	char *tmp;

	tmp = ft_strdup(shell->unparsed_com);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	shell->history = shell->history->prev;
	print_line(shell);
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
	free(tmp);
}

void				history_cursor_done(t_shell *shell)
{
	char *tmp;

	tmp = ft_strdup(shell->history->record);
	while (shell->position)
		symbol_del(shell);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, tmp, ft_strlen(tmp));
	shell->history = shell->history->prev;
	print_line(shell);
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
	free(tmp);
}

void				history_up(t_shell *shell)
{
	if (!(shell->history->prev))
		return ;
	if (shell->position < shell->length)
	{
		// printf("*\n");
		history_cursor_middle(shell);}
	else if (shell->unparsed_com[0])
	{
		// printf("!\n");
		history_cursor_edition(shell);
	}
	else if (shell->position == shell->length)
	{
		// printf("?\n");
		history_cursor_done(shell);}
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
