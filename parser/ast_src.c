/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_src.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:25:49 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/13 19:25:16 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ast               *leaf_creation_(t_tokens **tokens, int del, int del2)
{
    t_ast       *new;
    t_tokens    *tmp;

    if ((*tokens)->next == NULL)
        return (NULL);
    new = (t_ast *)malloc(sizeof(t_ast));
    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    new->type = (*tokens)->type;
    new->data = (char *)malloc(sizeof(char) * 2048);
    new->tokens = (*tokens);
    tmp = (*tokens)->next;
    while (tmp->next && (tmp->type != del && tmp->type != del2))
        tmp = tmp->next;
    tmp->prev->next = NULL;
    tmp->prev = NULL;
    *tokens = tmp;
    // printf("[%s]\n", (*tokens)->info);
    return (new);
}

t_ast	            *create_node(t_ast *left, t_ast *node, t_ast *right)
{
    // printf("[%s]\n",right->tokens->next->info);
	node->left = left;
	node->right = right;
	if (left)
		left->parent = node;
	if (right)
		right->parent = node;
	return (node);
}

int                 next_operator(t_tokens *tokens, int del)
{
    t_tokens *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == del)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
