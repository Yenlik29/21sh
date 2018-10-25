/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 20:10:25 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/24 15:49:50 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ds;
	unsigned const char	*sr;
	size_t				i;

	i = 0;
	ds = (unsigned char *)dst;
	sr = (unsigned const char *)src;
	while (i < n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (dst);
}
