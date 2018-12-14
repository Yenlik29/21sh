/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:16:09 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/14 19:30:47 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int                 shell_quotes(t_shell *shell)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (shell->history->record[i])
    {
        // printf("%c->", shell->history->record[i]);
        if (shell->history->record[i] == '\'')
            count++;
        i++;
    }
    return (count);
    // printf();
    // printf("[%s]\n", shell->history->record);
    // shell = NULL;
}
