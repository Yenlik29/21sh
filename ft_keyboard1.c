/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:53:45 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/26 13:53:46 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				enter_ch(t_shell *shell, uint64_t ch)
{
	char *tmp;
	int  count;

	tmp = (char *)malloc(sizeof(char) * 2048);
	if (shell->position == 0 && shell->length)
	{
		ft_strclr(tmp);
		tmp = ft_strncat(tmp, shell->unparsed_com, ft_strlen(shell->unparsed_com));
		ft_strclr(shell->unparsed_com);
		shell->unparsed_com[0] = ch;
		shell->unparsed_com = ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
		count = shell->length;
		while (count--)
			tputs(tgetstr("dc", NULL), 1, re_putchar);
		shell->length = ft_strlen(shell->unparsed_com);
		ft_putstr(shell->unparsed_com);
		count = shell->length;
		while (--count)
			tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position = 1;
		// free(tmp);
	}
	else
	{
		shell->unparsed_com[shell->length] = ch;
		write(0, &(shell->unparsed_com[shell->length]), 1);
		shell->length++;
		shell->position++;
	}
}

void 				left_key(t_shell *shell)
{
	if (shell->position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		(shell->position)--;
	}
}

void 				right_key(t_shell *shell)
{
	if (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
}

