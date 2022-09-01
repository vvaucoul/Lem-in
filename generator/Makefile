# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/14 14:04:36 by vvaucoul          #+#    #+#              #
#    Updated: 2022/07/14 16:40:26 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../Colors.mk

CC = clang-11
CFLAGS = -Wall -Wextra -g3 #-Werror
NAME = generator

SRCS =	generator.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@printf "\r$(_LWHITE)Compiling: $(_BOLD)$(_LGREEN)%s$(_END)\n" $<
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\n"
	@$(CC) $(CFLAGS) $(OBJS) ../libft.a -o $@
	@printf "$(_BOLD)$(_BLINK)$(_LGREEN)$(NAME) $(_LWHITE)compiled !\n$(_END)"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re