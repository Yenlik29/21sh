/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:10:31 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:10:32 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char			**ft_pwd(char **envp, char *word, char *pwd)
{
	envp[len_env(envp)] = ft_strjoin(word, pwd);
	return (envp);
}

void			ft_print_without_env(char *w_splited, char **envp)
{
	int i;

	i = 0;
	if (w_splited == NULL)
		ft_opt_require_arg('u');
	else
	{
		while (envp[i])
		{
			if (!(ft_strnequ(envp[i], w_splited, ft_strlen(w_splited))))
				ft_putendl(envp[i]);
			i++;
		}
	}
}

void			ft_parse_env(char **w_splited, char **envp)
{
	int i;

	i = 0;
	if (w_splited[1][0] == '-')
	{
		if (w_splited[1][1] == 'u')
			ft_print_without_env(w_splited[2], envp);
		else
			ft_illegal_env_opt(w_splited[1][1]);
	}
	else
	{
		if (access(w_splited[1], F_OK) != 0)
			ft_no_such_file_env_1(w_splited[1]);
		else
			ft_permission_env(w_splited[1]);
	}
}

int				ft_env_check(char *w_splited)
{
	if (w_splited[0] == '$')
		return (1);
	return (0);
}

char			**envp_create(char **env, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
