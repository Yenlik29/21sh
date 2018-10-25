/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:11:47 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/24 12:38:15 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *curr;

	curr = (unsigned char *)b;
	if (len == 0)
		return (b);
	while (len--)
	{
		*curr = (unsigned char)c;
		curr++;
	}
	return (b);
}
