/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:36:21 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/23 17:47:55 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_wordcount(char const *s, char c)
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

static	size_t	ft_wordlen(char const *s, char c)
{
	size_t i;
	size_t n;

	i = 0;
	n = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		n++;
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**w;

	i = 0;
	k = 0;
	if (!s || !(w = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1))))
		return (NULL);
	while (i < ft_wordcount(s, c))
	{
		if (!(w[i] = (char *)malloc(sizeof(char) * (ft_wordlen(s, c) + 1))))
			return (NULL);
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
			w[i][j++] = s[k++];
		w[i][j] = '\0';
		i++;
	}
	w[i] = NULL;
	return (w);
}
