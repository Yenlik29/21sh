/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:38:25 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/12 23:41:48 by ybokina          ###   ########.fr       */
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
        // if (next_operator(*tokens, T_PIPE))
        // {
            // printf("*\n");
            while ((*tokens)->type == T_PIPE)
            {
                // printf("[%s]\n", (*tokens)->info);
                root = create_node(root, leaf_creation_(tokens, T_SEMI, T_SEMI), leaf_creation_(tokens, T_PIPE, T_SEMI));
            }
        // }
        // else
            // printf("?\n");
            // root = create_node(root, leaf_creation_(tokens, -1), leaf_creation_(tokens, T_PIPE));
    }
    // print_ast(root, "root", 0);
    return (root);
}

t_ast                *create_ast(t_tokens **tokens)
{
    t_ast   *root;

    root = create_command(tokens);
    // if ((*tokens)->type == T_SEMI)
    // {
    //     if (next_operator(*tokens, T_SEMI))
    //     {
    //         while ((*tokens)->type == T_SEMI)
    //             root = create_node(root, leaf_creation_(tokens, -1), create_command(tokens));
    //     }
    //     else
    //         root = create_node(root, leaf_creation_(tokens, -1), create_command(tokens));
    // }
    return (root);
}
