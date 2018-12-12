/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:01:02 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/12 21:01:48 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_padding(int padd)
{
	int	i;

	i = 0;
	while (++i < padd)
		write(1, "\t", 1);
}

void	ft_print_node(t_ast *ast, char *side, int lvl)
{
	t_tokens *tmp;

	ft_padding(lvl);
	ft_putstr("** ");
	ft_putstr(side);
	ft_putnbr(lvl);
	ft_putendl(" **");
	ft_padding(lvl);
	tmp = ast->tokens;
	// ft_putstr(BMAGENTA);
	while (tmp)
	{
		ft_putstr(tmp->info);
		ft_putstr(" ");
		tmp = tmp->next;
	}
	// ft_putendl(RESET);
	ft_padding(lvl);
	ft_putendl("************");
}

void	print_ast(t_ast *ast, char *side, int lvl)
{
	if (lvl == 0)
		ft_putendl("________________ AST ________________");
	if (!ast)
		return ;
	if (ast->left)
		print_ast(ast->left, "left", ++lvl);
	else
		++lvl;
	ft_print_node(ast, side, lvl);
	if (ast->right)
		print_ast(ast->right, "right", lvl--);
	else
		--lvl;
	if (lvl == 0)
		ft_putendl("_____________________________________");
}