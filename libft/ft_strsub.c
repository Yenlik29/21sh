/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 20:31:10 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/25 22:30:58 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	s1 = (char *)malloc(sizeof(char) * len + 1);
	if (s1 == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		s1[i] = s[start];
		start++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
