/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:10:17 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:10:20 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			*ft_change(char *str, char *join, char *home_path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(join, home_path);
	ft_strdel(&str);
	str = ft_strdup(temp);
	(temp != NULL) ? free(temp) : NULL;
	return (str);
}

void			ft_default2(int *var1, int *var2)
{
	*var1 = 0;
	*var2 = 0;
}

void			ft_default(int *i, int *flag1, int *flag2)
{
	*i = 0;
	*flag1 = 0;
	*flag2 = 0;
}

int				ft_quote_len(char **w_splited)
{
	int	q;
	int	i;
	int	j;

	q = 0;
	i = 0;
	while (w_splited[++i])
	{
		j = 0;
		while (w_splited[i][j])
		{
			if (IS_QUOTE(w_splited[i][j]))
				q++;
			j++;
		}
	}
	return (q);
}

void			display_prompt(void)
{
	ft_putstr("\033[38;5;203m~\033[38;5;208m~\033[38;5;220m>\033[0m");
}
