/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:10:44 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:10:45 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char				**str_split1(char **w, char *s, char c, size_t i)
{
	int j;
	int	k;

	k = 0;
	while (++i < word_count(s, c))
	{
		j = 0;
		w[i] = ft_strnew(1024);
		while (s[k] == c && s[k + 1])
			k++;
		while (s[k] != c && s[k])
			w[i][j++] = s[k++];
		while (s[k] == c)
			k++;
		if (s[k] == c && s[k + 1] == '\0')
		{
			j = 0;
			w[i++] = ft_strnew(1024);
			w[i][j++] = c;
			k++;
		}
		w[i][j] = '\0';
	}
	w[i] = NULL;
	return (w);
}

char				**ft_new_envp(char **envp, char *new)
{
	envp[len_env(envp)] = ft_strdup(new);
	envp[len_env(envp)] = NULL;
	return (envp);
}
