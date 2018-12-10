/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:00:39 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/10 23:00:06 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// hello \"world              '   " ; echo 'hello$'

void					s_word_quote(t_lexer **tokens, int *j)
{
	// *state = S_QUOTE;
	(*tokens)->t_tokens->info[(*j)++] = T_QUOTE;
	(*tokens)->t_tokens->type = -1;
}

void					s_word_double_q(t_lexer **tokens, int *j)
{
	// *state = S_DOUBLE_Q;
	(*tokens)->t_tokens->info[(*j)++] = T_DOUBLE_Q;
	(*tokens)->t_tokens->type = -1;
}

void					s_word_esc(t_lexer **tokens, int *j, int *i, t_shell *shell)
{
	(*tokens)->t_tokens->info[(*j)++] = shell->history->record[++(*i)];
	(*tokens)->t_tokens->type = -1;
}

void					s_word_word(t_lexer **tokens, t_shell *shell, int *j, int *i)
{
	if (shell->history->record[(*i)] >= '1' && shell->history->record[(*i)] <= '9' && get_token_type(shell->history->record[((*i) + 1)]) == T_L_REDIR && get_token_type(shell->history->record[((*i) + 2)]) == T_AMPERSAND && shell->history->record[((*i) + 3)] >= '1' && shell->history->record[((*i) + 3)] <= '9' && (shell->history->record[(*i) + 4] == '\0' || shell->history->record[(*i) + 4] == ' '))
	{
		if ((*j) > 0)
		{
			(*tokens)->t_tokens->info[(*j)] = 0;
			*tokens = add_token(*tokens);
			(*tokens)->quantity++;
			(*tokens)->t_tokens = (*tokens)->t_tokens->next;
			*j = 0;
		}
		(*tokens)->t_tokens->info[0] = shell->history->record[(*i)];
		(*tokens)->t_tokens->info[1] = shell->history->record[(*i + 1)];
		(*tokens)->t_tokens->info[2] = shell->history->record[(*i + 2)];
		(*tokens)->t_tokens->info[3] = shell->history->record[(*i + 3)];
		(*tokens)->t_tokens->info[4] = '\0';
		(*tokens)->t_tokens->type = 144;
		*tokens = add_token(*tokens);
		(*tokens)->quantity++;
		(*tokens)->t_tokens = (*tokens)->t_tokens->next;
		(*i) = (*i) + 3;
	}
	else if (shell->history->record[(*i)] >= '1' && shell->history->record[(*i)] <= '9' && get_token_type(shell->history->record[((*i) + 1)]) == T_R_REDIR && get_token_type(shell->history->record[((*i) + 2)]) == T_AMPERSAND && shell->history->record[((*i) + 3)] >= '1' && shell->history->record[((*i) + 3)] <= '9' && (shell->history->record[(*i) + 4] == '\0' || shell->history->record[(*i) + 4] == ' '))
	{
		if ((*j) > 0)
		{
			(*tokens)->t_tokens->info[(*j)] = 0;
			*tokens = add_token(*tokens);
			(*tokens)->quantity++;
			(*tokens)->t_tokens = (*tokens)->t_tokens->next;
			*j = 0;
		}
		(*tokens)->t_tokens->info[0] = shell->history->record[(*i)];
		(*tokens)->t_tokens->info[1] = shell->history->record[(*i + 1)];
		(*tokens)->t_tokens->info[2] = shell->history->record[(*i + 2)];
		(*tokens)->t_tokens->info[3] = shell->history->record[(*i + 3)];
		(*tokens)->t_tokens->info[4] = '\0';
		(*tokens)->t_tokens->type = 146;
		*tokens = add_token(*tokens);
		(*tokens)->quantity++;
		(*tokens)->t_tokens = (*tokens)->t_tokens->next;
		(*i) = (*i) + 3;
	}
	else
	{
		(*tokens)->t_tokens->info[(*j)++] = shell->history->record[(*i)];
		(*tokens)->t_tokens->type = -1;
	}
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
