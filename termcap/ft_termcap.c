/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:20:08 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/26 13:20:08 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					key_hooker(uint64_t ch, int ret, t_shell *shell)
{
	ret = 0; //////////////////////////////////////
	if (ch == 127)
		symbol_del(shell);
	else if (ch >= 32 && ch < 127)
		enter_ch(shell, ch);
	else if (ch == 4283163)
		history_up(shell);
	else if (ch == 4348699)
		printf("DOWN\n");
	else if (ch == 4414235)
		right_key(shell);
	else if (ch == 4479771)
		left_key(shell);
	else if (ch == 25115)
		alt_left_key(shell);
	else if (ch == 26139)
		alt_right_key(shell);
	else if (ch == 4741915)
		printf("HOME\n");
	else if (ch == 4610843)
		printf("END\n");
	else if (ch == 74982532143899)
		printf("1 COL UP\n");
	else if (ch == 73883020516123)
		printf("1 COL DOWN\n");
	else
		return (0);
	return (1);
}