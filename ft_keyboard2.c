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

char 				*find_end(char *end, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < shell->position)
		i++;
	while (shell->unparsed_com[i])
	{
		end[j] = shell->unparsed_com[i];
		j++;
		i++;
	}
	end[j] = '\0';
	return (end);
}

void				middle_cursor(t_shell *shell, uint64_t ch)
{
	char *tmp;
	int  count;
	char *begin;
	char *end;
	int  i;

	tmp = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(tmp);
	tmp[0] = ch;
	begin = (char *)malloc(sizeof(char) * 2048);
	ft_strncat(begin, shell->unparsed_com, shell->position);
	// printf("[s->p%d:%d]\n", shell->position, shell->length);
	// printf("[%s]\n", begin);
	count = shell->length;
	while (count--)
		tputs(tgetstr("dc", NULL), 1, re_putchar);
	// end = (char *)malloc(sizeof(char) * 2048);
	// end = find_end(end, shell);
	// count = ft_strlen(end);
	// ft_strclr(shell->unparsed_com);
	// ft_strncat(shell->unparsed_com, begin, ft_strlen(begin));
	// ft_strncat(shell->unparsed_com, tmp, ft_strlen(tmp));
	// i = ft_strlen(shell->unparsed_com);
	// ft_strncat(shell->unparsed_com, end, ft_strlen(end));
	// shell->length = ft_strlen(shell->unparsed_com);
	// while (--i)
	// 	tputs(tgetstr("dc", NULL), 1, re_putchar);
	// // while (count--)
	// // 	tputs(tgetstr("dc", NULL), 1, re_putchar);
	// shell->length = ft_strlen(shell->unparsed_com);

	// printf("[%d]\n", count);
	// ft_putstr(shell->unparsed_com);
	free(tmp);
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