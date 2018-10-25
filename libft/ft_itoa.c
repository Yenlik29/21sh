/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:30:25 by ybokina           #+#    #+#             */
/*   Updated: 2018/03/23 17:48:09 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_itoa(char *itoad, int nbr, int i)
{
	int flag;

	flag = 1;
	if (nbr < 0)
	{
		itoad[0] = '-';
		flag = -1;
	}
	itoad[i] = '\0';
	i--;
	if (nbr == 0)
		itoad[i] = '0';
	while (i >= 0 && nbr != 0)
	{
		itoad[i--] = flag * (nbr % 10) + '0';
		nbr /= 10;
	}
	return (itoad);
}

static int	ft_numlength(int nbr)
{
	int n;

	n = 0;
	if (nbr <= 0)
		n++;
	while (nbr != 0)
	{
		nbr /= 10;
		n++;
	}
	return (n);
}

char		*ft_itoa(int n)
{
	char	*itoad;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_numlength(n);
	itoad = (char *)malloc(sizeof(char) * (i + 1));
	if (!itoad)
		return (NULL);
	itoad = fill_itoa(itoad, n, i);
	return (itoad);
}
