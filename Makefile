# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/31 09:06:42 by mo0ky             #+#    #+#              #
#    Updated: 2017/08/09 14:38:12 by mo0ky            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

ifdef FLAGS
	ifeq ($(FLAGS), no)
		CFLAGS=
	endif
	ifeq ($(FLAGS), debug)
		CFLAGS= -Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
	CFLAGS = -Wall -Wextra -Werror
endif

CC = gcc $(CFLAGS)

INC_PATH = includes

INCS = $(INC_PATH)/ft_printf.h

SRCS_PATH = sources
SRCS =	$(SRCS_PATH)/ft_printf.c		\
		$(SRCS_PATH)/init.c				\
		$(SRCS_PATH)/format_string.c

LIB_PATH = libft
LIB = $(LIB_PATH)/libft.a

OBJS	= $(SRCS:%.c=%.o)
C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(LIB) $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	@ar rcs $(NAME) $(OBJS)
	@libtool -static -o $(NAME) $(OBJS) $(LIB)
	@echo $(C_LGREEN)"$(NAME) compiled"$(C_DFL)

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) -I $(INC_PATH) -I $(LIB_PATH)/$(INC_PATH) -c -o $@ $<
	@$(ECHO) 'Linking' $@
	@echo  ".........."$(C_LGREEN)✓$(C_DFL)

clean: 
	@make clean -C $(LIB_PATH) 
	@for i in $(OBJS); \
	do if [ -e $$i ]; \
		then echo 'Deleting' $$i  ".........."$(C_RED)✗$(C_DFL);\
			/bin/rm -f $$i; \
		fi; \
	done
	@echo $(C_LRED)"Objects files deleted."$(C_DFL)

fclean: clean
	@make fclean -C $(LIB_PATH)
	@/bin/rm -f $(NAME)
	@echo $(C_RED)"Librairy $(NAME) deleted."$(C_DFL)

re: fclean all

.PHONY: objects OBJS clean fclean