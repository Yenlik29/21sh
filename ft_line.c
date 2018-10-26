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
		//PROVERKI NA KEYS;
		// word = ft_strncat(word, &ch, 6);
	}
	printf("%d:%d\n", shell->length, shell->position);
	write(0, "\n", 1);
		// if (word[i] )
		// else
		// 	break ;
	// }
	// if (word[0] == 127)
	// 	printf("BACKSPACE\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 65)
	// 	printf("UP\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 66)
	// 	printf("DOWN\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 67)
	// 	printf("RIGHT\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 68)
	// 	printf("LEFT\n");
	// if (word[0] == 27 && word[1] == 98)
	// 	printf("ALT+LEFT\n");
	// if (word[0] == 27 && word[1] == 102)
	// 	printf("ALT+RIGHT\n");
	// if (word[0] == 27 && word[1] == 65)
	// 	printf("ALT+UP\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 72)
	// 	printf("HOME\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 70)
	// 	printf("END\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 49 && word[3] == 59 && word[4] == 50 && word[5] == 68)
	// 	printf("1 COL UP\n");
	// if (word[0] == 27 && word[1] == 91 && word[2] == 49 && word[3] == 59 && word[4] == 50 && word[5] == 67)
	// 	printf("1 COL DOWN\n");
	// if (word[0] == 4)
	// 	printf("EOF\n");


	// w_splited = split_word(word);
	// w_splited = parsed_word(w_splited, env);
	// ft_bzero(word, ft_strlen(word));
	// (word != NULL) ? free(word) : NULL;
	return (w_splited);
}
