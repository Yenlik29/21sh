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

int 					parse_init(t_tokens *tokens, ASTnode **syntax_tree, int quantity)
{
	t_tokens *current;

	// printf("[%d]\n", tokens->quantity);
	// printf("*\n");
	if (quantity == 1 && !(ft_strcmp(tokens->info, "")))
	{
		// printf("*\n");
		return (-1);
	}
	current = tokens;
	// printf("*\n");
	*syntax_tree = command_line(&current);
	// if (current != NULL && current->type != 0)
	// {
	// 	printf("[%s]\n", "Syntax Error !");
	// 	return (-1);
	// }
	return (0);
}

ASTnode					*command_line(t_tokens **tokens)
{
	t_tokens	*save;
	ASTnode		*node;

	save = *tokens;
	// int i = 0;
	// printf("%d\n", i++);
	// printf("*\n");
	if ((*tokens = save, node = command_line1(tokens)) != NULL)
		return (node);
	return (NULL);
}

ASTnode					*command_line1(t_tokens **tokens)
{
	ASTnode		*cur;
	ASTnode		*cmd_line;
	ASTnode		*result;

	// printf("*\n");
	if ((cur = job(tokens)) == NULL)
		return (NULL);
	result = NULL;
	cmd_line = NULL;
	return (result);
}

ASTnode					*job(t_tokens **tokens)
{
	t_tokens	*save;
	ASTnode		*node;

	save = *tokens;
	// printf("*\n");
	// printf("^%s^\n", tokens->info);
	if ((*tokens = save, node = job1(tokens)) != NULL)
		return (node);
	return (node);
}

ASTnode					*job1(t_tokens **tokens)
{
	ASTnode		*cmd;
	ASTnode		*job;
	ASTnode		*result;

	if ((cmd = command(tokens)) == NULL)
		return (NULL);
	result = NULL;
	job = NULL;
	return (result);
}

ASTnode					*command(t_tokens **tokens)
{
	t_tokens	*save;
	ASTnode		*node;

	save = *tokens;
	if ((*tokens = save, node = command1(tokens)) != NULL)
		return (node);
	return (NULL);
}

ASTnode					*command1(t_tokens **tokens)
{
	ASTnode		*simple_com;
	ASTnode		*result;


	if ((simple_com = simple_cmd(tokens)) == NULL)
		return (NULL);
	result = NULL;
	return (result);
}

ASTnode					*simple_cmd(t_tokens **tokens)
{
	t_tokens	*save;

	save = *tokens;
	return (simple_cmd1(tokens));
}

ASTnode					*simple_cmd1(t_tokens **tokens)
{
	char		*path;
	ASTnode		*tokenList;
	ASTnode		*result;

	if (!term_(-1, &path, tokens))
	{	
		return (NULL);
	}
	tokenList = tokenlist(tokens);
	result = NULL;
	// // tokenList = NULL;
	return (result);
}

ASTnode					*tokenlist(t_tokens **tokens)
{
	t_tokens	*save;
	ASTnode		*node;

	save = *tokens;
	if ((*tokens = save, node = tokenlist1(tokens)) != NULL)
		return (node);
	if ((*tokens = save, node = tokenlist2()) != NULL)
		return (node);
	return (NULL);
}

ASTnode					*tokenlist1(t_tokens **tokens)
{
	ASTnode		*tokenlistNode;
	ASTnode		*result;
	char		*tmp;

	// printf("!\n");
	// while (tokens)
	// {
	// 	printf("^%s^\n", tokens->info);
	// tokens = tokens->next;
	// }
	if (!term_(-1, &tmp, tokens))
		return (NULL);

	// while (*tokens)
	// {
	// 	printf("[%s]\n", (*tokens)->info);
	// 	(*tokens) = (*tokens)->next;
	// }
	// tokenlistNode = NULL;
	tokenlistNode = tokenlist(tokens);

	if (!(result = (ASTnode *)malloc(sizeof(ASTnode) * 2048)))
		return (NULL);

	ASTnodeType(result, 64);
	ASTnodeData(result, tmp);
	ASTnodeAttach(result, NULL, tokenlistNode);
	// tokens = tokens->next;
	return (result);
}

ASTnode					*tokenlist2(void)
{
	return (NULL);
}

void					ASTnodeType(ASTnode *node, N_TYPE NodeType)
{
	if (node != NULL)
		node->type = NodeType;
}

void					ASTnodeData(ASTnode *node, char *data)
{
	if (node != NULL)
	{
		if (data != NULL)
		{
			node->data = data;
			node->type = N_DATA;
		}
	}
}

void					ASTnodeAttach(ASTnode *root, ASTnode *left, ASTnode *right)
{
	if (root != NULL)
	{
		root->left = left;
		root->right = right;
	}
}

int						term_(int toketype, char **buf, t_tokens **tokens)
{
	if (*tokens == NULL)
		return (0);
	// printf("[%s]\n", (*tokens)->info);
	if ((*tokens)->type == toketype && *tokens)
	{
		// printf("[%s]\n", (*tokens)->info);
		if (buf != NULL)
		{
			*buf = malloc(ft_strlen((*tokens)->info) + 1);
			ft_strcpy(*buf, (*tokens)->info);
		}
		*tokens = (*tokens)->next;
		return (1);
	}
	*tokens = (*tokens)->next;
	return (0);
}
