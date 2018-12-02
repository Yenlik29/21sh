/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:00:39 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/02 18:00:48 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_lexer					*add_token(t_lexer *tokens)
{
	t_tokens *tmp;
	t_tokens *new_node;

	if (!(new_node = (t_tokens *)malloc(sizeof(t_tokens))))
		return (NULL);
	tmp = tokens->t_tokens;
	if (tokens->t_tokens == NULL)
	{
		tokens->t_tokens = new_node;
		return (NULL);
	}
	if (!(new_node->info = (char *)malloc(sizeof(char) * 2048)))
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	new_node->next = NULL;
	return (tokens);
}
