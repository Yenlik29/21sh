/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:06:12 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/05 13:06:12 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int 				correct_operators(t_tokens *tokens)
{
	t_tokens *tmp;

	tmp = tokens;
	while (tmp)
	{
		// printf("[%s->%d]\n", tmp->info, tmp->type);
		// if ()
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
