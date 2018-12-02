/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:51:10 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/02 16:51:26 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_lexer				*lexer_allocation(t_lexer *tokens)
{
	if (!(tokens = (t_lexer *)malloc(sizeof(t_lexer) * 2048)))
		return (NULL);
	if (!(tokens->t_tokens = (t_tokens *)malloc(sizeof(t_tokens) * 2048)))
		return (NULL);
	tokens->quantity = 0;
	return (tokens);
}

t_tokens			*new_token(t_tokens *new)
{
	if (!(new->info = (char *)malloc(sizeof(char) * 2048)))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int 				get_token_type(char c)
{
	if (c == PIPE)
		return (T_PIPE);
	else if (c == SEMI)
		return (T_SEMI);
	else if (c == ' ')
		return (T_SPACE);
	else if (c == '\\')
		return (T_ESC);
	else if (c == '\t')
		return (T_TAB);
	else if (c == '&')
		return (T_AMPERSAND);
	else if (c == '\'')
		return (T_QUOTE);
	else if (c == '\"')
		return (T_DOUBLE_Q);
	else if (c == '\n')
		return (T_N_LINE);
	else if (c == '>')
		return (T_R_REDIR);
	else if (c == '<')
		return (T_L_REDIR);
	else
		return (T_WORD);
}

t_lexer				*lexer_build(t_lexer *tokens, t_shell *shell)
{
	int i;
	int state;
	int type;
	char *tmp;

	i = 0;
	state = S_WORD;
	tmp = NULL;
	tmp = ft_strdup(shell->history->record);
	tokens->t_tokens = new_token(tokens->t_tokens);
	while (shell->history->record[i])
	{
		type = get_token_type(shell->history->record[i]);
		// printf("[%d]\n", type);
		i++;
	}
	(tmp) ? free(tmp) : 0;
	return (tokens);
}

t_lexer				*lexer_init(t_lexer *tokens, t_shell *shell)
{
	if (!(tokens = lexer_allocation(tokens)))
		return (NULL);
	tokens = lexer_build(tokens, shell);
	return (tokens);
}

