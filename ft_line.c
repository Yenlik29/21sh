/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:11:59 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/18 12:16:41 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			**ft_word(char **word, char **env)
{
	int j;

	j = 0;
	while (word[j])
	{
		// printf("*[%s]", word[j]);
		if ((word[j][0] == '~' && word[j][1] == '\0') ||
			(word[j][0] == '~' && word[j][1] == '/'))
			word[j] = ft_tilda(env, word[j]);
		if (ft_env_check(word[j]) == 1)
			word[j] = ft_dollar(env, word[j]);
		// printf("!\n");
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

char			**read_line(char **env, t_shell *shell)
{
	uint64_t		ch;
	ssize_t			ret;
	// char			*word;
	int				quotes;

	quotes = 0;
	ret = 0;
	ch = 0;
	// word = ft_strnew(4096);
	while ((ret = read(0, &ch, 6) && ch != '\n') > 0)
	{
		if (key_hooker(ch, ret, shell) == 0)
			break ;
		ch = 0;
	}

	/* ДОБАВЬ ЭТО ВСЕ В ФАЙЛ ft_line_src.c */

	quotes = shell_quotes(shell);
	// printf("[%d]\n", quotes);
	shell->start = 0;
	shell->end = 0;
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	ft_strclr(shell->unparsed_com);

	t_lexer		*tokens;
	t_tokens	*temp;
	t_ast		*syntax_tree;

	tokens = NULL;
	temp = NULL;
	tokens = lexer_init(tokens, shell, &temp);

	// int l = 0;
	// while (temp->next)
	// {
	// 	printf("[%s]\n", temp->info);
	// 	temp = temp->next;
	// }
	syntax_tree = parse(temp); /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WORKING HEEEREEE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	

	char **w_splited;
	
	w_splited = NULL;
	// printf("???\n");
	// print_ast(syntax_tree, "root", 0);
	env = execution(syntax_tree, shell, env, w_splited);
	// printf("????\n");
	// printf("[%d]\n", syntax_tree->type);

	// w_splited = split_word(shell->history->record);
	// w_splited = parsed_word(w_splited, env);
	// ft_bzero(word, ft_strlen(word));
	// (word != NULL) ? free(word) : NULL;
	// printf("->%s", w_splited);
	// if (w_splited)

		// free_2darray(&w_splited);
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
	}
	return (env);
	// env = NULL;
}

// echo $PWD; pwd; ls ; echo $HOME; ls -a ~/Desktop
