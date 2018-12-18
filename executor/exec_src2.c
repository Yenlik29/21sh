/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_src2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:58:56 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/18 15:59:10 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					redir_quant(t_ast *ast)
{
	int quant;
	t_ast *temp;

	quant = 0;
	temp = ast;
	while (temp->tokens)
	{
		if (!(ft_strcmp(temp->tokens->info, ">")) || !(ft_strcmp(temp->tokens->info, ">>")) || !(ft_strcmp(temp->tokens->info, "<")) || !(ft_strcmp(temp->tokens->info, "<<")))
			quant++;
		if (temp->tokens->next)
            temp->tokens = temp->tokens->next;
        else
            break ;
	}
	return (quant);
}

void				simple_redir(t_ast *temp, char *file, char **env)
{
	int 	fd;
	char 	**new;
    t_ast 	*tmp;

    new = NULL;
    tmp = temp;
    // write(0, tmp->tokens->next->info, ft_strlen(tmp->tokens->next->info));
    fd = open(file, O_CREAT|O_APPEND|O_RDWR, 0777);
    new = cmd_create(tmp, new);
    new = parsed_word(new, env);
    if (fd < 0)
        exit(0);
    dup2(fd, STDOUT_FILENO);
    ft_available_command(new, env);
    close(fd);
    // exit(0);
}

char				**cmd_create(t_ast *ast, char **cmd)
{
	int i;

	i = 0;
	cmd = (char **)malloc(sizeof(char *) * 2048);
	while (ast->tokens)
	{
		if (ast->tokens->prev)
			ast->tokens = ast->tokens->prev;
		else
			break ;
	}
	while (ast->tokens)
	{
		if (!ft_strcmp(ast->tokens->info, ">"))
			break ;
		cmd[i] = (char *)malloc(sizeof(char) * 2048);
		ft_strclr(cmd[i]);
		ft_strncpy(cmd[i], ast->tokens->info, ft_strlen(ast->tokens->info));
		if (ast->tokens->next)
			ast->tokens = ast->tokens->next;
		else
			break ;
		i++;
	}
	return (cmd);
}
