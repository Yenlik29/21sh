/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:51:10 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/13 20:14:17 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_lexer				*lexer_allocation(t_lexer *tokens)
{
	if (!(tokens = (t_lexer *)malloc(sizeof(t_lexer) * 2048)))
		return (NULL);
	if (!(tokens->t_tokens = (t_tokens *)malloc(sizeof(t_tokens) * 2048)))
		return (NULL);
	tokens->quantity = 1;
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
	if (c == '|')
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
	int j;
	int state;
	int type;

	i = 0;
	j = 0;
	state = S_WORD;
	tokens->t_tokens = new_token(tokens->t_tokens);
	write(1, "\n", 1);
	while (shell->history->record[i])
	{
		// printf("[%c]\n", shell->history->record[i]);
		type = get_token_type(shell->history->record[i]);
		if (state == S_WORD)
		{
			s_word(&tokens, &j, &i, shell);
			(get_token_type(shell->history->record[i]) == T_QUOTE) ? state = S_QUOTE : 0;
			(get_token_type(shell->history->record[i]) == T_DOUBLE_Q) ? state = S_DOUBLE_Q : 0;
		}
		else if (state == S_QUOTE)
		{
			s_quote(&tokens, &j, shell, &i);
			(get_token_type(shell->history->record[i]) == T_QUOTE && shell->history->record[(i) + 1] == ' ') ? state = S_WORD : 0;
		}
		else if (state == S_DOUBLE_Q)
			s_double_q_(&tokens, &j, shell->history->record[i], &state);
		i++;
	}
	if (!(shell->history->record[i]))
		printf("DOBAV' TOKEN \\0\n");
	return (tokens);
}
























































// t_lexer				*lexer_build(t_lexer *tokens, t_shell *shell)
// {
// 	return (tokens);
// }


















t_lexer				*lexer_init(t_lexer *tokens, t_shell *shell, t_tokens **temp)
{
	if (!(tokens = lexer_allocation(tokens)))
		return (NULL);
	*temp = tokens->t_tokens;
	tokens = lexer_build(tokens, shell);
	return (tokens);
}

