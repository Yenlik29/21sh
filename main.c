/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:12:42 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:12:43 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			sighandler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		display_prompt();
		signal(SIGINT, sighandler);
	}
}

void			loop(char **env)
{
	char	**w_splited;

	while (42)
	{
		w_splited = NULL;
		display_prompt();
		signal(SIGINT, sighandler);
		w_splited = read_line(env, w_splited);
		if (w_splited[0] != NULL)
			env = ft_core(w_splited, env);
		free_2darray(&w_splited);
	}
}

int				main(int argc, char **argv, char **envp)
{
	char	**env;
	

	env = (char **)malloc(sizeof(char *) * 1024);
	env = envp_create(env, envp);
	if (terminal_init() <= 0)
		return (0);
	if (terminal_define() == 0)
		return (0);
	loop(env);
	argv = NULL;
	argc = 0;
	return (0);
}
