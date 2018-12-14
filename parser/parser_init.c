/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:06:12 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/14 11:36:28 by ybokina          ###   ########.fr       */
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
			return (1);
		}
		else
			tmp->mistake = 0;
		tmp = tmp->next;
	}
	return (0);
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

t_ast				*parse(t_tokens *tokens)
{
	t_ast 		*ast;
	t_tokens	*temp;

	temp = tokens;
	if (correct_operators(temp) == 1 || correct_pre_post(temp) == 1)
		return (NULL);
	// temp = tokens;
	// while (temp)
	// {
	// 	printf("[%s]\n", temp->info);
	// 	if (temp->next)
	// 		temp = temp->next;
	// 	else
	// 		break ;
	// }
	ast = create_ast(&temp);
	return (ast);
	// print_ast(ast, "root", 0);
}
