/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:00:29 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/25 17:44:00 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = dst;
	while (src[i] != '\0' && len)
	{
		if (!len)
			return (dst);
		dst[i] = src[i];
		i++;
		len--;
	}
	while (len--)
	{
		dst[i] = 0;
		i++;
	}
	return (ret);
}
