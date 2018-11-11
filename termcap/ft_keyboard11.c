/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard11.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:14:08 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/11 12:14:08 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			norm_edition(t_shell *shell, uint64_t ch)
{
	if (shell->position == 0 && shell->length)
		begin_cursor(shell, ch);
	else if (shell->position > 0 && shell->position < shell->length)
		middle_cursor(shell, ch);
	else
	{
		// printf("*\n");
		shell->unparsed_com[shell->length] = ch;
		shell->unparsed_com[shell->length + 1] = '\0';
		write(0, &(shell->unparsed_com[shell->length]), 1);
		shell->length = ft_strlen(shell->unparsed_com);
		shell->position++;
		ft_strclr(shell->history->record);
		ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
		// printf("[%s->%s:%d->%d]\n", shell->unparsed_com, shell->history->record, shell->position, shell->length);
	}
}
