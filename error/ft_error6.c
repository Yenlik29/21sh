/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:23:16 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/19 19:57:49 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			ft_error_tcsetattr(void)
{
	ft_putstr_fd("tcsetattr() error\n", 2);
}

void			pipe_fd_error(void)
{
	ft_putstr_fd("pipe() mistake\n", 2);
	exit(1);
}

void			fork_error(void)
{
	ft_putstr_fd("fork() error\n", 2);
	exit(1);
}

void			is_a_directory(char *str)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}
