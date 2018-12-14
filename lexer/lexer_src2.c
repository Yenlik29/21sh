/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_src2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:09:58 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/14 11:15:29 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                token_end(t_lexer **tokens, t_shell *shell, int *j, int *i)
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
    (*tokens)->t_tokens->info[1] = '\0';
    (*tokens)->t_tokens->type = 404;
    *tokens = add_token(*tokens);
    (*tokens)->quantity++;
    (*tokens)->t_tokens = (*tokens)->t_tokens->next;
    (*i)++;
}

void                s_word_mistake(t_lexer **tokens, t_shell *shell, int *j, int *i)
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
    (*tokens)->t_tokens->info[1] = shell->history->record[(*i) + 1];
    (*tokens)->t_tokens->info[2] = '\0';
    (*tokens)->t_tokens->type = 333;
    *tokens = add_token(*tokens);
    (*tokens)->quantity++;
    (*tokens)->t_tokens = (*tokens)->t_tokens->next;
    (*i)++;
}
