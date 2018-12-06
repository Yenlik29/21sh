/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:44:15 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/06 19:44:15 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				s_word_operator(t_lexer **tokens, int *nquant, int *j, char c)
{
	if ((*j) > 0)
	{
		(*tokens)->t_tokens->info[(*j)] = 0;
		*tokens = add_token(*tokens);
		(*nquant)++;
		(*tokens)->t_tokens = (*tokens)->t_tokens->next;
		*j = 0;
	}
	(*tokens)->t_tokens->info[0] = c;
	(*tokens)->t_tokens->info[1] = '\0';
	(*tokens)->t_tokens->type = get_token_type(c);
	*tokens = add_token(*tokens);
	(*nquant)++;
	(*tokens)->t_tokens = (*tokens)->t_tokens->next;
	
}

void				s_word_space(t_lexer **tokens, int *nquant, int *j)
{
	if ((*j) > 0)
	{
		(*tokens)->t_tokens->info[(*j)] = 0;
		*tokens = add_token(*tokens);
		(*nquant)++;
		(*tokens)->t_tokens = (*tokens)->t_tokens->next;
		(*j) = 0;
	}
}
