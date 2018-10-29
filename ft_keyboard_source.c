/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_source.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:28:02 by ybokina           #+#    #+#             */
/*   Updated: 2018/10/29 11:28:02 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char 				*end_record(char *end, t_shell *shell)
{
	end = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(end);
	end = find_end(end, shell);
	return (end);
}

char 				*begin_record(char *begin, t_shell *shell)
{
	begin = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(begin);
	ft_strncat(begin, shell->unparsed_com, shell->position);
	return (begin);
}

char 				*char_record(char ch, char *tmp)
{
	tmp = (char *)malloc(sizeof(char) * 2048);
	ft_strclr(tmp);
	tmp[0] = ch;
	return (tmp);
}

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

void				string_clear(t_shell *shell, int del)
{
	int count;

	count = shell->length - 1;
	while (count--)
		tputs(tgetstr("dc", NULL), 1, re_putchar);
	while (del--)
		tputs(tgetstr("le", NULL), 1, re_putchar);
}
















