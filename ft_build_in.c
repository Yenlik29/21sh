/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:09:15 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:09:17 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			ft_env(char **w_splited, char **envp)
{
	int i;

	i = 0;
	if (len_env(w_splited) == 1)
	{
		while (envp[i])
		{
			ft_putendl(envp[i]);
			i++;
		}
	}
	if (len_env(w_splited) > 3)
		ft_wrong_quantity_env();
	if (len_env(w_splited) == 2 || len_env(w_splited) == 3)
		ft_parse_env(w_splited, envp);
}

void			ft_putnstr(char *str, int n)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[++i] && i < (int)ft_strlen(str) + n)
			ft_putchar(str[i]);
	}
	else
	{
		while (str[++i] && i < n)
			ft_putchar(str[i]);
	}
}

void			echo(char **str, int pos)
{
	int		start;
	int		end;
	int		len;

	start = IS_QUOTE(str[pos][0]);
	len = (int)ft_strlen(str[pos]);
	end = IS_QUOTE(str[pos][len - 1]);
	if (end && start)
		ft_putnstr(str[pos] + 1, -1);
	else if (end)
		ft_putnstr(str[pos], -1);
	else if (start)
		ft_putstr(str[pos] + 1);
	else
		ft_putstr(str[pos]);
	if (str[pos + 1])
		ft_putchar(' ');
}

void			ft_echo(char **w_splited)
{
	int		i;
	int		n;
	int		q;

	ft_default(&n, &q, &i);
	if (!w_splited[1])
	{
		write(1, "\n", 1);
		return ;
	}
	else if (w_splited[1][0] == '-' &&
		w_splited[1][1] == 'n' && w_splited[1][2] == '\0')
		n = 1;
	q = ft_quote_len(w_splited);
	(n) ? ++i : i;
	(q != 2 && q != 0) ? ft_quote_error(q) : NULL;
	if ((q == 2 || q == 0) || n == 1)
	{
		while (w_splited[++i])
		{
			echo(w_splited, i);
			if (!w_splited[i + 1] && !n)
				ft_putchar('\n');
		}
	}
}

char			**ft_exec_buil_in(char **w_splited, char **envp)
{
	if (!(ft_strcmp(w_splited[0], "cd")))
		envp = ft_cd(w_splited, envp);
	if (!(ft_strcmp(w_splited[0], "setenv")))
		envp = ft_setenv(w_splited, envp);
	if (!(ft_strcmp(w_splited[0], "unsetenv")))
		envp = ft_unsetenv(w_splited, envp);
	if (!(ft_strcmp(w_splited[0], "env")))
		ft_env(w_splited, envp);
	if (!(ft_strcmp(w_splited[0], "echo")))
		ft_echo(w_splited);
	if (!(ft_strcmp(w_splited[0], "exit")))
		exit(0);
	return (envp);
}
