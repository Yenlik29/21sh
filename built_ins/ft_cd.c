/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 12:09:24 by ybokina           #+#    #+#             */
/*   Updated: 2018/08/23 12:09:26 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				ft_parsed_cd(char *w_splited)
{
	struct stat buf;

	lstat(w_splited, &buf);
	if (access(w_splited, F_OK) != 0)
	{
		ft_no_such_file(w_splited);
		return (0);
	}
	if (!(S_ISDIR(buf.st_mode)) && !(S_ISLNK(buf.st_mode)))
	{
		ft_not_directory(w_splited);
		return (0);
	}
	if (((access(w_splited, W_OK) == 0) && (access(w_splited, R_OK) != 0)
		&& (access(w_splited, X_OK) != 0)) || ((access(w_splited, W_OK) != 0)
		&& (access(w_splited, R_OK) == 0) && (access(w_splited, X_OK) != 0)) ||
		((access(w_splited, W_OK) == 0) && (access(w_splited, R_OK) == 0)
		&& (access(w_splited, X_OK) != 0)) || ((access(w_splited, W_OK) != 0)
		&& (access(w_splited, R_OK) != 0) && (access(w_splited, X_OK) != 0)))
	{
		ft_permission_denied(w_splited);
		return (0);
	}
	return (1);
}

char			**ft_chdir(char **envp, char *w_splited, char *pwd)
{
	char	*buf;
	char	*temp;

	buf = NULL;
	temp = NULL;
	if (chdir(w_splited) != 0)
	{
		ft_putstr_fd("chdir() failed\n", 2);
		return (envp);
	}
	ft_bzero(w_splited, ft_strlen(w_splited));
	temp = ft_join_f("", getcwd(buf, 1024));
	w_splited = ft_strcpy(w_splited, temp);
	envp = ft_envp(envp, w_splited, pwd);
	(temp != NULL) ? free(temp) : NULL;
	return (envp);
}

char			**ft_cd_one(char *w_splited, char **envp)
{
	char	*pwd;
	char	*buf;
	char	*old_pwd;

	buf = NULL;
	pwd = NULL;
	old_pwd = ft_join_f("", getcwd(buf, 1024));
	((w_splited[0] == '\0') || (w_splited[0] == '-' && w_splited[1] == '-' &&
	ft_strlen(w_splited) == 2)) ? pwd = ft_pwd0(envp, pwd) : NULL;
	if (!(w_splited[0] == '-' && ft_strlen(w_splited) == 1) &&
	(!(w_splited[0] == '-' && w_splited[1] == '-' &&
	ft_strlen(w_splited) == 2)))
	{
		if (ft_parsed_cd(w_splited) == 1)
		{
			envp = ft_chdir(envp, w_splited, old_pwd);
			free_2var(pwd, old_pwd);
			return (envp);
		}
	}
	if (w_splited[0] == '-' && ft_strlen(w_splited) == 1)
		pwd = ft_look(envp, pwd, "OLDPWD");
	(pwd != NULL) ? envp = ft_chdir(envp, pwd, old_pwd) : NULL;
	free_2var(pwd, old_pwd);
	return (envp);
}

char			**ft_only_cd(char **envp)
{
	char	*home_path;
	char	*cur_pwd;
	char	*old_pwd;
	char	*buf;

	buf = NULL;
	cur_pwd = NULL;
	home_path = (char *)malloc(sizeof(char) * 1024);
	home_path = ft_home(envp, home_path);
	old_pwd = ft_join_f("", getcwd(buf, 1024));
	if (home_path[0] == '\0')
	{
		free(home_path);
		home_path = getcwd(buf, 1024);
	}
	if (chdir(home_path) != 0)
	{
		ft_putstr_fd("chdir() failed\n", 2);
		free_3var(home_path, cur_pwd, old_pwd);
		return (envp);
	}
	cur_pwd = ft_join_f("", getcwd(buf, 1024));
	envp = ft_change_envp1(envp, home_path, cur_pwd, old_pwd);
	free_3var(home_path, cur_pwd, old_pwd);
	return (envp);
}

char			**ft_cd(char **w_splited, char **envp)
{
	int		len;

	len = len_env(w_splited);
	if (len == 2)
		envp = ft_cd_one(w_splited[1], envp);
	if (len == 3)
		envp = ft_cd_two(w_splited, envp);
	if (len > 3)
		ft_putstr_fd("cd: too many arguments\n", 2);
	if (len == 1)
		envp = ft_only_cd(envp);
	return (envp);
}
