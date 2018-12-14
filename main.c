/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:12:42 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/14 16:28:44 by ybokina          ###   ########.fr       */
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

t_shell 		*init_shell(t_shell *shell)
{
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!(shell->history = (t_history *)malloc(sizeof(t_history))))
		return (NULL);
	shell->history->next = NULL;
	shell->history->prev = NULL;
	shell->start = 0;
	shell->end = 0;
	shell->buf = (char *)malloc(sizeof(char) * 2048);
	shell->tmp = (char *)malloc(sizeof(char) * 2048);
	shell->unparsed_com = (char *)malloc(sizeof(char) * 4089);
	shell->length = 0;
	shell->position = 0;
	return (shell);
}

void			loop(char **env)
{
	t_shell *shell;
	char	**w_splited;

	shell = NULL;
	shell = init_shell(shell);
	new_history(shell);
	while (42)
	{
		w_splited = NULL;
		display_prompt();
		signal(SIGINT, sighandler);
		w_splited = read_line(env, w_splited, shell);
		shell = shell_reset(shell);
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
