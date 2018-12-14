/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:38:25 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/14 11:31:20 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ast               *create_command(t_tokens **tokens)
{
    t_ast       *root;

    root = leaf_creation_(tokens, T_PIPE, T_SEMI);  
    // printf("[%s]\n", (*tokens)->info);
    if ((*tokens)->type == T_PIPE)
    {
        while ((*tokens)->type == T_PIPE)
        {
            // printf("[%s]\n", (*tokens)->info);
            root = create_node(root, leaf_creation_(tokens, -1, -1), leaf_creation_(tokens, T_PIPE, T_SEMI));
        }
    }
    // print_ast(root, "root", 0);
    return (root);
}

t_ast                *create_ast(t_tokens **tokens)
{
    t_ast   *root;

    root = create_command(tokens);
    if ((*tokens)->type == T_SEMI)
    {
        // if (next_operator(*tokens, T_SEMI))
        // {
            while ((*tokens)->type == T_SEMI)
                root = create_node(root, leaf_creation_(tokens, -1, -1), create_command(tokens));
        // }
        // else
        //     root = create_node(root, leaf_creation_(tokens, -1), create_command(tokens));
    }
    print_ast(root, "root", 0);
    return (root);
}
