/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:03:36 by ybokina           #+#    #+#             */
/*   Updated: 2018/11/07 15:03:44 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				shift_left_end(t_shell *shell)
{
	char *tmp;

	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	tmp = ft_strdup(shell->history->record);
	shell->length = ft_strlen(shell->history->record);
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->position = 0;
	shell->history = shell->history->prev;
	ft_strclr(shell->history->next->record);
	ft_strncat(shell->history->next->record, tmp, ft_strlen(tmp));
	print_line(shell);
	shell->length = ft_strlen(shell->history->record);
	shell->position = shell->length;
}

void				shift_left_norm(t_shell *shell)
{
	char *tmp;
	int position;

	position = shell->position;
	ft_strclr(shell->history->record);
	ft_strncat(shell->history->record, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	tmp = ft_strdup(shell->history->record);
	while (shell->position != shell->length)
	{
		tputs(tgetstr("nd", NULL), 1, re_putchar);
		shell->position++;
	}
	clear_till_begin(shell);
	shell->history = shell->history->prev;
	ft_strclr(shell->history->next->record);
	ft_strncat(shell->history->next->record, tmp, ft_strlen(tmp));
	print_line(shell);
	shell->position = ft_strlen(shell->history->record);
	while (shell->position != position)
	{
		tputs(tgetstr("le", NULL), 1, re_putchar);
		shell->position--;
	}
	shell->length = ft_strlen(shell->history->record);
}

void				shift_left(t_shell *shell)
{
	if (!(shell->history->prev))
		return ;
	if (shell->position > (int)ft_strlen(shell->history->prev->record))
		shift_left_end(shell);
	else
		shift_left_norm(shell);
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, shell->history->record, ft_strlen(shell->history->record));
}

void				end_key(t_shell *shell)
{
	if (shell->position == shell->length)
		return ;
	while (shell->position != shell->length)
	{
		if (check_cursor(shell) == 0)
			multi_end_key(shell);
		else
			norm_end_key(shell);
	}
}

void				home_key(t_shell *shell)
{
	if (shell->position == 0)
		return ;
	else if (shell->position <= shell->length)
	{
		if (check_cursor(shell) == 0)
			multi_home_key(shell);
		else
			norm_home_key(shell);
	}
}
