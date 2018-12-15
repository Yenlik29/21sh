/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:23:16 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/25 15:23:17 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			ft_error_tcsetattr(void)
{
	ft_putstr_fd("tcsetattr() error\n", 2);
}

void			pipe_fd_error()
{
	ft_putstr_fd("pipe() mistake\n", 2);
	exit(1);
}
