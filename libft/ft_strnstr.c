/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 11:45:40 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/25 19:40:06 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (!*big)
		return (0);
	if (ft_strlen((char *)little) > len)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i] == little[j]) && big[i] && little[j] && i < len)
		{
			i++;
			j++;
		}
		if (j == (size_t)ft_strlen(little))
			return ((char *)big + i - j);
		else
			i = (i - j) + 1;
		j = 0;
	}
	return (NULL);
}
