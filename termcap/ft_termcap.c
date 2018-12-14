/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybokina <ybokina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:20:08 by ybokina           #+#    #+#             */
/*   Updated: 2018/12/14 18:24:42 by ybokina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				key_hooker2(uint64_t ch, t_shell *shell)
{
	if (ch == 25115)
		alt_left_key(shell);
	else if (ch == 26139)
		alt_right_key(shell);
	else if (ch == 4741915)
		home_key(shell);
	else if (ch == 4610843)
		end_key(shell);
	else if (ch == 74982532143899)
		shift_left(shell);
	else if (ch == 73883020516123)
		shift_right(shell);
	else
		key_hooker3(ch, shell);
}

void				key_hooker3(uint64_t ch, t_shell *shell)
{
	if (ch == 23)
		cut(shell);
	else if (ch == 27)
		left_selection(shell);
	else if (ch == 29)
		right_selection(shell);
	else if (ch == 5)
		copy(shell);
	else if (ch == 18)
		paste(shell);
	else
		key_hooker4(ch, shell);
}

int				key_hooker4(uint64_t ch, t_shell *shell)
{
	if (ch == 4)
		printf("CTRL+D\n");
	else if (ch == 478560413032)
		printf("CMD+V\n");
	else if (ch == 16)
		play_music();
	else if (ch == 12)
		stop_music();
	else
	{
		printf("hey\n");
		shell = NULL;
		// printf("[%2c]", (char)ch);
		// printf("[%2c]", (char)ch + 1);
		// printf("[%2c]", (char)ch + 2);
		// printf("[%2c]", (char)ch + 3);
		// printf("[%2c]", (char)ch + 4);
		// printf("[%2c]", (char)ch + 5);
		// printf("[%2c]\n", (char)ch);

		return (0);
	}
	return (1);
}

int					key_hooker(uint64_t ch, int ret, t_shell *shell)
{
	// int		state;

	// state = S_WORD;
	ret = 0;
	if (ch == 127)
		symbol_del(shell);
	else if (ch >= 32 && ch < 127)
		enter_ch(shell, ch);
	else if (ch == 4283163)
		history_up(shell);
	else if (ch == 4348699)
		history_down(shell);
	else if (ch == 4414235)
		right_key(shell);
	else if (ch == 4479771)
		left_key(shell);
	else
		key_hooker2(ch, shell);
	// printf("[%lld]\n", ch);
	ft_strclr(shell->tmp);
	ft_strncat(shell->tmp, shell->unparsed_com, ft_strlen(shell->unparsed_com));
	// printf("[%s]\n", shell->tmp);
	return (1);
}