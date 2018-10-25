/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:12:23 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:12:23 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			**ft_edit_envp(char *new, char *w_splited, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if ((ft_strnequ(envp[i], new, ft_strlen(new))) == 1)
		{
			if ((int)ft_strlen(new) == ft_count_before(envp[i], '='))
			{
				ft_strclr(envp[i]);
				envp[i] = ft_strcat(envp[i], w_splited);
			}
		}
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char			**ft_setenv_work(char *w_splited, char **envp)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	new = (char *)malloc(sizeof(char) * 1024);
	while (w_splited[i] != '=')
	{
		new[i] = w_splited[i];
		i++;
	}
	new[i] = '\0';
	if (ft_parse_name(new, envp) == 1)
		envp = ft_edit_envp(new, w_splited, envp);
	else
		envp = ft_new_envp(envp, w_splited);
	(new != NULL) ? free(new) : NULL;
	return (envp);
}

int				ft_parse_name(char *name, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if ((ft_strnequ(envp[i], name, ft_strlen(name))) == 1)
		{
			if (((int)ft_strlen(name)) == ft_count_before(envp[i], '='))
				return (1);
		}
		i++;
	}
	return (0);
}

int				ft_parse_setenv(char *w_splited)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (w_splited[i])
	{
		if (w_splited[i] == '=')
			count++;
		i++;
	}
	if (ft_strchr(w_splited, '=') != 0 && count == 1)
		return (1);
	else
	{
		ft_setenv_parse_error(w_splited);
		return (0);
	}
	return (0);
}

char			**ft_setenv(char **w_splited, char **envp)
{
	int		len;

	len = (len_env(w_splited));
	if (len == 1)
		ft_setenv_arg_error();
	else if (len == 2)
	{
		if (ft_parse_setenv(w_splited[1]) == 1)
			envp = ft_setenv_work(w_splited[1], envp);
	}
	else
		ft_setenv_overload();
	return (envp);
}
