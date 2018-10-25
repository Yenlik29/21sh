/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:04:00 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/26 17:43:42 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isempty(char const *str)
{
	char *ptr;

	ptr = (char *)str;
	while (*ptr)
	{
		if (!((unsigned char)*ptr <= 32))
			return (0);
		ptr++;
	}
	return (1);
}
