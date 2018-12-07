/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:44:15 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/07 18:29:47 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				s_word_double_l_redir(t_lexer **tokens, t_shell *shell, int *j, int *i)
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
	(*tokens)->t_tokens->info[1] = shell->history->record[(*i)++];
	(*tokens)->t_tokens->info[2] = '\0';
	(*tokens)->t_tokens->type = 142;
	*tokens = add_token(*tokens);
	(*tokens)->quantity++;
	(*tokens)->t_tokens = (*tokens)->t_tokens->next;
	*j = 0;
}

void				s_word_double_r_redir(t_lexer **tokens, t_shell *shell, int *j, int *i)
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
	(*tokens)->t_tokens->info[1] = shell->history->record[(*i)++];
	(*tokens)->t_tokens->info[2] = '\0';
	(*tokens)->t_tokens->type = 140;
	*tokens = add_token(*tokens);
	(*tokens)->quantity++;
	(*tokens)->t_tokens = (*tokens)->t_tokens->next;
	*j = 0;
}

void				s_word_operator(t_lexer **tokens, int *j, char c)
{
	printf("*");
	if ((*j) > 0)
	{
		(*tokens)->t_tokens->info[(*j)] = 0;
		*tokens = add_token(*tokens);
		(*tokens)->quantity++;
		(*tokens)->t_tokens = (*tokens)->t_tokens->next;
		*j = 0;
	}
	(*tokens)->t_tokens->info[0] = c;
	(*tokens)->t_tokens->info[1] = '\0';
	(*tokens)->t_tokens->type = get_token_type(c);
	*tokens = add_token(*tokens);
	(*tokens)->quantity++;
	(*tokens)->t_tokens = (*tokens)->t_tokens->next;
	
}

void				s_word_space(t_lexer **tokens, int *j)
{
	if ((*j) > 0)
	{
		(*tokens)->t_tokens->info[(*j)] = 0;
		*tokens = add_token(*tokens);
		(*tokens)->quantity++;
		(*tokens)->t_tokens = (*tokens)->t_tokens->next;
		(*j) = 0;
	}
}
