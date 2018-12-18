/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_src.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:22:14 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/18 14:25:10 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void                redir_exec(char **w_splited, char **env, t_ast *left)
{
    int i;

    t_ast *temp;

    i = 0;
    temp = left;
    while (temp->tokens)
    {
        if (temp->tokens->prev)
            temp->tokens = temp->tokens->prev;
        else
            break ;
    }
    int quant;
    quant = 0;
    quant = redir_quant(temp);
    while (temp->tokens)
    {
        if (temp->tokens->prev)
            temp->tokens = temp->tokens->prev;
        else
            break ;
    }
    char *red;
    char *file;

    file = (char *)malloc(sizeof(char) * 2048);
    red = (char *)malloc(sizeof(char) * 2048);
    while (temp->tokens)
    {
        if (!(ft_strcmp(temp->tokens->info, ">")) || !(ft_strcmp(temp->tokens->info, ">>")) || !(ft_strcmp(temp->tokens->info, "<")) || !(ft_strcmp(temp->tokens->info, "<<")))
        {
            ft_strclr(red);
            ft_strncpy(red, temp->tokens->info, ft_strlen(temp->tokens->info));
            ft_strclr(file);
            ft_strncpy(file, temp->tokens->next->info, ft_strlen(temp->tokens->next->info));
            i++;
        }
        if (temp->tokens->next)
            temp->tokens = temp->tokens->next;
        else
            break ;
    }
    simple_redir(temp, file, env);
    while (temp->tokens)
    {
        if (temp->tokens->prev)
            temp->tokens = temp->tokens->prev;
        else
            break ;
    }
    // write(0, ft_itoa(i), ft_strlen(ft_itoa(i)));
    // write(0, "- ", ft_strlen("- "));
    // write(0, red, ft_strlen(red));
    // write(0, "- ", ft_strlen("- "));
    // write(0, file, ft_strlen(file));
    // write(0, "\n", ft_strlen("\n"));
    w_splited = NULL;
    env = NULL;
}

void                stand_exec(char **w_splited, char **env, int fd[2])
{
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    ft_available_command(w_splited, env); 
    // exit(0);
}

int                 check_redir(char **w_splited)
{
    int l;

    l = 0;
    while (w_splited[l])
    {
        if (!(ft_strcmp(w_splited[l], ">")))
            return (1);
        l++;
    }
    return (0);
}

char                **array_assign(t_ast *ast, char **w_splited)
{
    int i;

    i = 0;
    if (!(w_splited = (char **)malloc(sizeof(char) * 2048)))
        return (NULL);
    while (ast->tokens && ast->tokens->info[0])
    {
        if (!(w_splited[i] = (char *)malloc(sizeof(char) * 2048)))
            return (NULL);
        ft_strclr(w_splited[i]);
        ft_strncpy(w_splited[i], ast->tokens->info, ft_strlen(ast->tokens->info));
        if (ast->tokens->next)
            ast->tokens = ast->tokens->next;
        else
        {
            i++;
            w_splited[i] = NULL;
            return (w_splited);
        }
        i++;
    }
    w_splited[i] = NULL;
    return (w_splited);
}
