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

// hello \"world              '   " ; echo 'hello$'

void					s_word_quote(int *state, t_lexer **tokens, int *j)
{
	*state = S_QUOTE;
	(*tokens)->t_tokens->info[(*j)++] = T_QUOTE;
	(*tokens)->t_tokens->type = -1;
}

void					s_word_double_q(int *state, t_lexer **tokens, int *j)
{
	*state = S_DOUBLE_Q;
	(*tokens)->t_tokens->info[(*j)++] = T_DOUBLE_Q;
	(*tokens)->t_tokens->type = -1;
}

void					s_word_esc(t_lexer **tokens, int *j, int *i, t_shell *shell)
{
	(*tokens)->t_tokens->info[(*j)++] = shell->history->record[++(*i)];
	(*tokens)->t_tokens->type = -1;
}

void					s_word_word(t_lexer **tokens, int *j, char c)
{
	(*tokens)->t_tokens->info[(*j)++] = c;
	(*tokens)->t_tokens->type = -1;
}

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
