/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_src.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 20:13:04 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/10 22:34:49 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                s_word(t_lexer **tokens, int *j, int *i, t_shell *shell)
{
    if (get_token_type(shell->history->record[(*i)]) == T_QUOTE)
        s_word_quote(tokens, j);
    else if (get_token_type(shell->history->record[(*i)]) == T_DOUBLE_Q)
        s_word_double_q(tokens, j);
    else if (get_token_type(shell->history->record[(*i)]) == T_ESC)
        s_word_esc(tokens, j, i, shell);
    else if (get_token_type(shell->history->record[(*i)]) == T_WORD)
        s_word_word(tokens, shell, j, i);
    else if (get_token_type(shell->history->record[(*i)]) == T_SPACE)
        s_word_space(tokens, j);
    else if (get_token_type(shell->history->record[(*i)]) == T_SEMI || get_token_type(shell->history->record[(*i)]) == T_R_REDIR || get_token_type(shell->history->record[(*i)]) == T_L_REDIR || get_token_type(shell->history->record[(*i)]) == T_AMPERSAND || get_token_type(shell->history->record[(*i)]) == T_PIPE)
    {
        if (get_token_type(shell->history->record[(*i)]) == T_R_REDIR && shell->history->record[(*i) + 1] == '>' && (shell->history->record[(*i) + 2] == '\0' || (shell->history->record[(*i) + 2] >= 32 && shell->history->record[(*i) + 2] < 127)))
            s_word_double_r_redir(tokens, shell, j, i);
        else if (get_token_type(shell->history->record[(*i)]) == T_L_REDIR && get_token_type(shell->history->record[((*i) + 1)]) == T_L_REDIR && shell->history->record[(*i) + 2] == '-' && (shell->history->record[(*i) + 3] == '\0' || (shell->history->record[(*i) + 3] >= 32 && shell->history->record[(*i) + 3] < 127)))
            s_word_heredoc(tokens, shell, j, i);
        else if (get_token_type(shell->history->record[(*i)]) == T_L_REDIR && shell->history->record[(*i) + 1] == '<' && (shell->history->record[(*i) + 2] == '\0' || (shell->history->record[(*i) + 2] >= 32 && shell->history->record[(*i) + 2] < 127)))
            s_word_double_l_redir(tokens, shell, j, i);
        else
            s_word_operator(tokens, j, shell->history->record[*i]);
    }
}

void                s_quote(t_lexer **tokens, int *j, t_shell *shell, int *i)
{
    (*tokens)->t_tokens->info[(*j)++] = shell->history->record[(*i)];
    if (get_token_type(shell->history->record[(*i)]) == T_QUOTE && shell->history->record[(*i) + 1] == ' ')
    {
        (*tokens)->t_tokens->info[(*j)++] = 0;
        *tokens = add_token(*tokens);
        (*tokens)->quantity++;
        (*tokens)->t_tokens = (*tokens)->t_tokens->next;
        *j = 0;
    }
}

void                s_double_q_(t_lexer **tokens, int *j, char c, int *state)
{
    (*tokens)->t_tokens->info[(*j)++] = c;
    if (get_token_type(c) == T_DOUBLE_Q)
    {
        *state = S_WORD;
        (*tokens)->t_tokens->info[(*j)++] = 0;
        *tokens = add_token(*tokens);
        (*tokens)->quantity++;
        (*tokens)->t_tokens = (*tokens)->t_tokens->next;
        *j = 0;
    }
}
