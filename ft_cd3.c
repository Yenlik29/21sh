/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:09:55 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:09:58 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				ft_splited_parse(char **w_splited)
{
	int	i;

	i = 1;
	while (w_splited[i])
	{
		if (ft_parsed_cd(w_splited[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void			ft_free_not_cwd(char *w_splited)
{
	ft_not_in_cwd(w_splited);
}

int				ft_parsed_cd2(char **w_splited)
{
	char			*buf;
	char			*temp;
	int				ret;

	buf = NULL;
	temp = NULL;
	ret = 0;
	temp = ft_join_f("", getcwd(buf, 1024));
	if (ft_strcmp(temp, w_splited[1]))
	{
		ft_free_not_cwd(w_splited[1]);
		(temp != NULL) ? free(temp) : NULL;
		return (0);
	}
	ret = ft_splited_parse(w_splited);
	if (ret == 0)
	{
		(temp != NULL) ? free(temp) : NULL;
		return (0);
	}
	(temp != NULL) ? free(temp) : NULL;
	return (1);
}

char			**ft_cd_two(char **w_splited, char **envp)
{
	if (ft_parsed_cd2(w_splited) == 1)
		ft_chdir(envp, w_splited[2], w_splited[1]);
	return (envp);
}
