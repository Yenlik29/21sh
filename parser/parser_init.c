/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:06:12 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/11 14:29:15 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void 				correct_operators(t_tokens *tokens)
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
}

int						correct_pre_post(t_tokens *tokens)
{
	t_tokens *temp;

	temp = tokens;
	while (temp)
	{
		if ((temp->type == 124 && !temp->prev) || (temp->type == 38 && !temp->prev))
		{
			ft_putstr_fd("21sh: syntax error\n", 1);
			temp->mistake = 1;
		}
		else if (temp->type == 124 && temp->next->type != -1)
		{
			ft_putstr_fd("21sh: syntax error\n", 1);
			return (1);
		}
		else if ((temp->type == 62 || temp->type == 60 || temp->type == 140 || temp->type == 142 || temp->type == 144 || temp->type == 146 || temp->type == 148) && temp->next->type != -1)
		{
			ft_putstr_fd("21sh: syntax error\n", 1);
			return (1);
		}
		else
			temp->mistake = 0;
		temp = temp->next;
	}
	return (0);
}

void				parse(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = tokens;
	correct_operators(temp);
	if (correct_pre_post(temp) == 1)
		return ;
}
