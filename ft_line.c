/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:11:59 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:12:00 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			**ft_word(char **word, char **env)
{
	int j;

	j = 0;
	while (word[j])
	{
		if ((word[j][0] == '~' && word[j][1] == '\0') ||
			(word[j][0] == '~' && word[j][1] == '/'))
			word[j] = ft_tilda(env, word[j]);
		if (ft_env_check(word[j]) == 1)
			word[j] = ft_dollar(env, word[j]);
		j++;
	}
	return (word);
}

char			**parsed_word(char **word, char **env)
{
	word = ft_word(word, env);
	return (word);
}

char			**str_split(char *s, char c)
{
	size_t	i;
	size_t	k;
	char	**w;

	i = -1;
	k = 0;
	if (!s || !(w = (char **)malloc(sizeof(char *) * 1024)))
		return (NULL);
	if (s[0] == c && !s[k + 1])
	{
		w[0] = (char *)(malloc(sizeof(char) * 2));
		w[0][0] = c;
		w[0][1] = '\0';
		return (w);
	}
	w = str_split1(w, s, c, i);
	return (w);
}

char			**split_word(char *word)
{
	char	**command;
	char	*sentence;

	sentence = NULL;
	command = NULL;
	sentence = (char *)malloc(sizeof(char) * 1024);
	sentence = ft_check(sentence, word, '\t');
	command = str_split(sentence, ' ');
	(sentence != NULL) ? free(sentence) : NULL;
	return (command);
}

char			**read_line(char **env, char **w_splited, t_shell *shell)
{
	uint64_t		ch;
	ssize_t			ret;
	char			*word;
	int				i;

	i = 0;
	ret = 0;
	ch = 0;
	word = ft_strnew(4096);
	while ((ret = read(0, &ch, 6) && ch != '\n') > 0)
	{
		if (key_hooker(ch, ret, shell) == 0)
			break ;
		ch = 0;
	}
	// printf("[%s]\n", shell->buf);
	shell->start = 0;
	shell->end = 0;
	// printf("\n\n[%s]\n", shell->buf);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	ft_strclr(shell->unparsed_com);

	t_lexer		*tokens;
	// t_lexer 	*tmp;
	t_tokens	*temp;
	// ASTnode		*syntax_tree;

	tokens = NULL;
	temp = NULL;
	// syntax_tree = (ASTnode *)malloc(sizeof(ASTnode) * 10);
	// tokens->quantity = 0;
	// temp = tokens->t_tokens;
	tokens = lexer_init(tokens, shell, &temp);
	// tmp = tokens;
	// while (temp)
	// {
	// 	printf("[%s]\n", temp->info);
	// 	temp = temp->next;
	// }
	parse(temp); /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WORKING HEEEREEE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	// parse_init(temp, &syntax_tree, tokens->quantity);


	w_splited = split_word(shell->history->record);
	w_splited = parsed_word(w_splited, env);


	ft_bzero(word, ft_strlen(word));
	(word != NULL) ? free(word) : NULL;

	while (shell->history->next != NULL)
			shell->history = shell->history->next;

	shell = add_history(shell);
	ft_strclr(shell->buf);
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->tmp, ft_strlen(shell->tmp));
	shell->length = ft_strlen(shell->history->record);
	shell->history = shell->history->next;
	if (shell->position == shell->length)
		write(0, "\n", 1);
	else
	{
		end_key(shell);
		set_cursor(shell);
		write(0, "\n", 1);
		// printf("*\n");
	}
	return (w_splited);
}
