/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:09:05 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:09:08 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				ft_find(char **envp, char *word)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnequ(envp[i], word, ft_strlen(word)) == 1)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_join_f(char *s1, char *s2)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	free(s2);
	return (tmp);
}

char			*ft_join_f2(char *s1, char *s2)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	return (tmp);
}

int				len_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

size_t			word_count(char const *s, char c)
{
	size_t i;
	size_t wd;

	i = 0;
	wd = 0;
	while (s[i])
	{
		if (s[i] != c)
			wd++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (wd);
}
