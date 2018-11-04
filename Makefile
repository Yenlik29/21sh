#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybokina <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 12:12:47 by ybokina           #+#    #+#              #
#    Updated: 2018/11/04 09:38:40 by ybokina          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include			21sh.mk

CC				:= gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -lft -L $(LIBFT_DIR) -ltermcap
	@printf "\r\033[38;5;117m✓ $(NAME) created\033[0m\033[K\n"

$(OBJS_DIR_BASE)/%.o: %.c $(HEADER)
	@printf "\033[38;5;117m\033[2KCompiling: $(@)\033[0m\033\r"
	@$(CC) -c $< -o $@ $(FLAGS) $(HEADER_FLAGS) -I.

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ): |$(OBJS_DIR)

$(OBJS_DIR):
	@mkdir $@

clean:
	@make -C libft clean
	@rm -rf $(OBJS_DIR_BASE)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
