/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:49 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/26 22:54:50 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				begin_cursor(t_shell *shell, uint64_t ch)
{
	char *tmp;
	int  count;
	
	tmp = (char *)malloc(sizeof(char) * 2048);
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
	free(tmp);
}