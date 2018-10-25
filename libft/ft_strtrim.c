/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 21:26:11 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/26 21:08:28 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_smth(char const *s, int *start, int *last)
{
	while (s[*start])
	{
		if (s[*start] != '\n' && s[*start] != '\t' && s[*start] != ' ')
			break ;
		*start = *start + 1;
	}
	while (s[*last] && *last + 1 >= *start)
	{
		if (s[*last] != '\n' && s[*last] != '\t' && s[*last] != ' ')
			break ;
		*last = *last - 1;
	}
}

char			*ft_strtrim(char const *s)
{
	int		start;
	int		last;
	char	*res;
	int		i;

	if (!s)
		return (0);
	last = ft_strlen(s) - 1;
	start = 0;
	ft_smth(s, &start, &last);
	res = ft_strnew(last - start + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= last)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
