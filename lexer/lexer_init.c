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
	char *tmp;
	int nquant;
	t_tokens *temp;

	i = 0;
	j = 0;
	nquant = 1;
	state = S_WORD;
	tmp = NULL;
	tmp = ft_strdup(shell->history->record);
	temp = tokens->t_tokens;
	tokens->t_tokens = new_token(tokens->t_tokens);
	printf("\n");
	while (shell->history->record[i])
	{
		type = get_token_type(shell->history->record[i]);
		if (state == S_WORD)
		{
			if (type == T_QUOTE)
			{
				// printf("Quote found\n");
				state = S_QUOTE;
				tokens->t_tokens->info[j++] = T_QUOTE;
				// printf("[%s]\n", tokens->t_tokens->info);
				tokens->t_tokens->type = -1;
			}
			else if (type == T_DOUBLE_Q)
			{
				// printf("Double Quote found\n");
				state = S_DOUBLE_Q;
				tokens->t_tokens->info[j++] = T_DOUBLE_Q;
				tokens->t_tokens->type = -1;
			}
			else if (type == T_ESC)
			{
				// printf("Esc\n");
				tokens->t_tokens->info[j++] = shell->history->record[++i];
				tokens->t_tokens->type = -1;
			}
			else if (type == T_WORD)
			{
				// printf("Ch->%c\n", shell->history->record[i]);
				tokens->t_tokens->info[j++] = shell->history->record[i];
				tokens->t_tokens->type = -1;
			}
			else if (type == T_SPACE)
			{
				// printf("Space->%c\n", shell->history->record[i]);
				if (j > 0)
				{
					
					tokens->t_tokens->info[j] = 0;
					tokens = add_token(tokens);
					nquant++;
					tokens->t_tokens = tokens->t_tokens->next;
					j = 0;
				}
			}
			else if (type == T_SEMI || type == T_R_REDIR || type == T_L_REDIR || type == T_AMPERSAND || type == T_PIPE)
			{
				// printf("Oper->%c\n", shell->history->record[i]);
				if (j > 0)
				{
					
					tokens->t_tokens->info[j] = 0;
					tokens = add_token(tokens);
					nquant++;
					tokens->t_tokens = tokens->t_tokens->next;
					j = 0;
				}
			}
		}
		else if (state == S_QUOTE)
		{
			tokens->t_tokens->info[j++] = shell->history->record[i];
			if (type == T_QUOTE)
				state = S_WORD;
		}
		else if (state == S_DOUBLE_Q)
		{
			tokens->t_tokens->info[j++] = shell->history->record[i];
			if (type == T_DOUBLE_Q)
				state = S_WORD;
		}
		i++;
	}
	// printf("[%d]\n", nquant);
	// int l = 0;
	// printf("[%s]\n", temp->info);
	while (temp)
	{
		printf("[%s]\n", temp->info);
		temp = temp->next;
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

