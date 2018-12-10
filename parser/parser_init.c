/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:06:12 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/10 23:25:42 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int 				correct_operators(t_tokens *tokens)
{
	t_tokens *tmp;

	tmp = tokens;
	// printf("?\n");
	// printf("[%s]\n", tmp->info);
	while (tmp)
	{
		// printf("[%s]\n", tmp->info);
		if (!(ft_strncmp(tmp->info, "&&", ft_strlen("&&"))) \
		|| !(ft_strncmp(tmp->info, "||", ft_strlen("||"))) \
		|| !(ft_strncmp(tmp->info, ";;", ft_strlen(";;"))) \
		|| !(ft_strncmp(tmp->info, "<>", ft_strlen("<>"))) \
		|| !(ft_strncmp(tmp->info, ">|", ft_strlen(">|"))))
		{
			ft_putstr_fd("21sh: syntax error\n", 1);
			tmp->mistake = 1;
		}
		else
			tmp->mistake = 0;
		tmp = tmp->next;
	}
	return (1);
}

void				parse(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = tokens;
	// printf("*\n");
	if (!(correct_operators(temp)))
		return ;
}
