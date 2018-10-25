/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:34:26 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/26 19:12:34 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	res;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] == '\n' || str[i] == '\t' || str[i] == '\r' ||
			str[i] == '\f' || str[i] == '\v' || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && res >= 0)
		res = res * 10 + (long long int)(str[i++] - '0');
	if (res < 0)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return ((int)res * (int)sign);
}
