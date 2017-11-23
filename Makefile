# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/31 09:06:42 by mo0ky             #+#    #+#              #
#    Updated: 2017/11/13 22:48:12 by mo0ky            ###   ########.fr        #
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

INCS = $(INC_PATH)/ft_printf.h	\
		$(INC_PATH)/fmt.h		\
		$(INC_PATH)/fmt_types.h

SRCS_PATH = sources
SRCS =	$(SRCS_PATH)/ft_printf.c		\
		$(SRCS_PATH)/analyze_format.c 	\
		$(SRCS_PATH)/get_format.c 	\
		$(SRCS_PATH)/format_string.c 	\
		$(SRCS_PATH)/do_filler.c 		\
		$(SRCS_PATH)/color.c 		\
		$(SRCS_PATH)/convch/parser.c			\
		$(SRCS_PATH)/convch/init_var/fmt.c		\
		$(SRCS_PATH)/convch/init_var/signed.c	\
		$(SRCS_PATH)/convch/init_var/unsigned.c	\
		$(SRCS_PATH)/convch/init_var/wchar1.c	\
		$(SRCS_PATH)/convch/convert/tools/utils_unsigned.c	\
		$(SRCS_PATH)/convch/convert/tools/do_preci_and_fill.c	\
		$(SRCS_PATH)/convch/convert/tools/do_sign.c	\
		$(SRCS_PATH)/convch/convert/tools/do_space.c	\
		$(SRCS_PATH)/convch/convert/tools/fix_counter.c	\
		$(SRCS_PATH)/convch/convert/tools/more_speed.c	\
		$(SRCS_PATH)/convch/convert/tools/ret_error.c	\
		$(SRCS_PATH)/convch/convert/char.c		\
		$(SRCS_PATH)/convch/convert/string.c	\
		$(SRCS_PATH)/convch/convert/wchar.c		\
		$(SRCS_PATH)/convch/convert/wstring.c	\
		$(SRCS_PATH)/convch/convert/uint.c		\
		$(SRCS_PATH)/convch/convert/int.c		\
		$(SRCS_PATH)/convch/convert/hexa.c		\
		$(SRCS_PATH)/convch/convert/octal.c		\
		$(SRCS_PATH)/convch/convert/binary.c		\
		$(SRCS_PATH)/convch/convert/no_convert.c

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
	@echo "Linking file" $@

clean: 
	@make clean -C $(LIB_PATH)
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIB_PATH)
	@if [ -e $(NAME) ]; \
	then echo $(C_RED)"Delete $(NAME)."$(C_DFL); \
	fi;
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: objects OBJS clean fclean