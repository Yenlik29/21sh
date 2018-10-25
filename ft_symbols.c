/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:12:29 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:12:29 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			*ft_home(char **env, char *home)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], "HOME", ft_strlen("HOME")) == 1)
		{
			home = ft_strcpy(home, ft_strchr(env[i], '=') + 1);
			return (home);
		}
		i++;
	}
	ft_bzero(home, ft_strlen(home));
	return (home);
}

char			*ft_check(char *sentence, char *word, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (word[i])
	{
		if (word[i] != c)
		{
			sentence[k] = word[i];
			k++;
		}
		while (word[i] == c)
			i++;
		if (word[i] != c && word[i - 1] == c)
		{
			sentence[k] = ' ';
			k++;
			sentence[k] = word[i];
			k++;
		}
		i++;
	}
	sentence[k] = '\0';
	return (sentence);
}

char			*ft_environments(char *word, char **new, char **env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	temp = ft_strnew(1024);
	while (new[++i])
	{
		j = -1;
		while (env[++j])
		{
			if (ft_strnequ(new[i], env[j], ft_strlen(new[i])) == 1)
			{
				if (((int)ft_strlen(new[i])) == ft_count_before(env[j], '='))
					temp = ft_join_f2(temp, ft_strchr(env[j], '=') + 1);
			}
		}
		if (!(ft_strcmp(new[i], "$")))
			temp = ft_join_f2(temp, "$");
		if (!(ft_strcmp(new[i], "<")) || !(ft_strcmp(new[i], ">")))
			ft_parse_error();
	}
	word = ft_strcpy(word, temp);
	(temp != NULL) ? free(temp) : NULL;
	return (word);
}

char			*ft_dollar(char **env, char *word)
{
	int		i;
	char	**new;

	i = 0;
	new = str_split(word, '$');
	ft_bzero(word, ft_strlen(word));
	word = ft_environments(word, new, env);
	if (new[0] != NULL)
		free_2darray(&new);
	return (word);
}

char			*ft_tilda(char **env, char *word)
{
	int		i;
	int		count;
	char	*home;
	char	*temp;

	ft_default2(&i, &count);
	temp = NULL;
	while (env[i])
	{
		if (ft_strnequ(env[i], "HOME", ft_strlen("HOME")) == 1)
		{
			count++;
			home = ft_strdup(ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	if (count == 0)
	{
		home = (char *)malloc(sizeof(char) * 1024);
		ft_bzero(home, ft_strlen(home));
	}
	temp = ft_strjoin(home, ft_strchr(word, '~') + 1);
	word = ft_strcpy(word, temp);
	free_2var(home, temp);
	return (word);
}
