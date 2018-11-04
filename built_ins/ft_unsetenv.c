/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:12:36 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:12:37 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			**ft_new_envp1(char **new_envp, char **envp, char *w_splited)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (envp[j])
	{
		if ((ft_strnequ(envp[j], w_splited, ft_strlen(w_splited))) == 1 &&
			((int)ft_strlen(w_splited) == ft_count_before(envp[j], '=')))
			j++;
		else
		{
			new_envp[k] = ft_strdup(envp[j]);
			k++;
			j++;
		}
	}
	new_envp[k] = NULL;
	return (new_envp);
}

char			**ft_unsetenv_work(char *w_splited, char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = (char **)malloc(sizeof(char *) * 1024);
	new_envp = ft_new_envp1(new_envp, envp, w_splited);
	if (new_envp[0] != NULL)
		free_2darray(&envp);
	envp = (char **)malloc(sizeof(char *) * 1024);
	while (new_envp[i])
	{
		envp[i] = ft_strdup(new_envp[i]);
		i++;
	}
	envp[i] = NULL;
	if (new_envp[0] != NULL)
		free_2darray(&new_envp);
	return (envp);
}

int				ft_parse_unset(char *w_splited)
{
	int		i;

	i = 0;
	while (w_splited[i])
	{
		if (w_splited[i] == '=')
		{
			ft_setenv_parse_error(w_splited);
			return (0);
		}
		i++;
	}
	return (1);
}

char			**ft_unsetenv(char **w_splited, char **envp)
{
	int		len;
	int		i;

	i = 0;
	len = (len_env(w_splited));
	if (len == 1)
		ft_setenv_arg_error();
	else if (len == 2)
	{
		if (ft_parse_unset(w_splited[1]) == 1)
		{
			if (ft_parse_name(w_splited[1], envp) == 1)
				envp = ft_unsetenv_work(w_splited[1], envp);
			else
				return (envp);
		}
	}
	else
		ft_setenv_overload();
	return (envp);
}
