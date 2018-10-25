/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:10:09 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:10:12 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_count_before(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int			ft_check_build_in(char **w_splited)
{
	if ((w_splited != NULL) && ft_strcmp(w_splited[0], "echo")
	&& ft_strcmp(w_splited[0], "cd") && ft_strcmp(w_splited[0], "setenv")
	&& ft_strcmp(w_splited[0], "unsetenv") && ft_strcmp(w_splited[0], "env")
	&& ft_strcmp(w_splited[0], "exit"))
	{
		return (0);
	}
	else
		return (1);
}

void		ft_available_command(char **command, char **envp)
{
	char			**path;

	path = NULL;
	if ((ft_if_path(command)) == 0)
		path = ft_path(envp);
	else
	{
		path = (char **)malloc(sizeof(char *) * 100);
		path = envp_create(path, command);
	}
	ft_exec_sys(path, command, envp);
	free_2darray(&path);
}

char		**ft_commands(char **w_splited, char **envp)
{
	pid_t	child_pid;
	int		stat_loc;
	int		res;

	res = 0;
	res = ft_check_build_in(w_splited);
	if (res == 1)
		envp = ft_exec_buil_in(w_splited, envp);
	if (res == 0)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			ft_available_command(w_splited, envp);
			exit(0);
		}
		else
			waitpid(child_pid, &stat_loc, WUNTRACED);
	}
	return (envp);
}

char		**ft_core(char **w_splited, char **env)
{
	env = ft_commands(w_splited, env);
	return (env);
}
