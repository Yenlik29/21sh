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

t_shell				*symbol_remove(t_shell *shell)
{
	int 	i;
	char 	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(tmp);
	while (i < shell->length - 1)
	{
		tmp[i] = shell->unparsed_com[i];
		i++;
	}
	tmp[i] = '\0';
	ft_strclr(shell->unparsed_com);
	ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
	free(tmp);
	return (shell);
}

void				middle_cursor(t_shell *shell, uint64_t ch)
{
	char *tmp;
	char *begin;
	char *end;
	int  del;
	int  cursor;

	tmp = char_record(ch, tmp);
	begin = begin_record(begin, shell);
	del = ft_strlen(begin);
	ft_strncat(begin, tmp, ft_strlen(tmp));
	end = end_record(end, shell);
	cursor = ft_strlen(end);
	ft_strncat(begin, end, ft_strlen(end));
	shell = shell_set_settings(shell, begin);
	string_clear(shell, del);
	ft_putstr(shell->unparsed_com);
	while (cursor--)
		tputs(tgetstr("le", NULL), 1, re_putchar);
	free(tmp);
	free(begin);
	free(end);
}

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