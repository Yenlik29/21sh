/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:06:12 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/10 23:55:31 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int 				correct_operators(t_tokens *tokens)
{
	t_tokens *ret;
	t_tokens *tmp;

	ret = tokens;
	tmp = tokens;
	while (tmp)
	{
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
	while (ret)
	{
		if (ret->mistake == 1)
			return (1);
		ret = ret->next;
	}
	return (0);
}

int					correct_pre_post(t_tokens *tokens)
{
	t_tokens *temp;

	temp = tokens;
	while (temp)
	{
		printf("[%s->%d]\n", temp->info, temp->type);
		if ((temp->type == 124 && !temp->prev))
		{
			ft_putstr_fd("21sh: syntax error\n", 1);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void				parse(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = tokens;
	if (!(correct_operators(temp)) || !(correct_pre_post(temp)))
		return ;
}
