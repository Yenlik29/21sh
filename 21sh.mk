# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    21sh.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybokina <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/04 09:23:53 by ybokina           #+#    #+#              #
#    Updated: 2018/11/04 09:39:32 by ybokina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= 21sh

ERRORS_DIR		:= error
TERMCAP_DIR		:= termcap
BUILT_INS_DIR	:= built_ins

OBJS_DIR_BASE	:= objs

OBJS_DIR 		:= $(OBJS_DIR_BASE)\
         		   $(OBJS_DIR_BASE)/$(ERRORS_DIR)\
         		   $(OBJS_DIR_BASE)/$(TERMCAP_DIR)\
         		   $(OBJS_DIR_BASE)/$(BUILT_INS_DIR)

FLAGS			:= -Wall -Wextra -Werror

SRCF			:= main.c					\
				   ft_display.c				\
				   ft_line.c				\
				   ft_symbols.c				\
				   ft_core.c				\
				   ft_free.c				\
				   ft_execution.c			\
				   ft_terminal.c			\
				   ft_history1.c

ERRORS_SRCF	   := ft_error1.c				\
                  ft_error2.c   			\
                  ft_error3.c   			\
                  ft_error4.c   			\
                  ft_error5.c   			\
                  ft_error6.c

TERMCAP_SRCF   := ft_termcap.c  			\
                  ft_keyboard1.c			\
                  ft_keyboard2.c			\
                  ft_keyboard_source.c		\
                  ft_keyboard3.c			\
                  ft_keyboard4.c			\
                  ft_keyboard5.c 

BUILT_INS_SRCF := ft_actions.c				\
				  ft_build_in.c 			\
				  ft_cd.c       			\
				  ft_cd2.c      			\
				  ft_cd3.c      			\
				  ft_env1.c     			\
				  ft_env2.c     			\
				  ft_path.c     			\
				  ft_setenv.c   			\
				  ft_unsetenv.c 


SOURCES 		:= $(SRCF) $(ERRORS_SRCF:%=$(ERRORS_DIR)/%)\
							$(TERMCAP_SRCF:%=$(TERMCAP_DIR)/%)\
								$(BUILT_INS_SRCF:%=$(BUILT_INS_DIR)/%)

OBJ				:= $(SOURCES:%.c=$(OBJS_DIR_BASE)/%.o)
HEADER			:= ft_21sh.h
LIBFT_DIR		:= libft/
LIBFT			:= $(LIBFT_DIR)libft.a
HEADER_FLAGS	:= -I $(LIBFT_DIR)
