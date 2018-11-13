/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard15.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:59:00 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/13 19:59:00 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				go_up_inline(t_shell *shell)
{
	if (check_cursor(shell) == 0)
			printf("Multi\n");
		else
			printf("Alone\n");
}
