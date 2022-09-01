# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 14:56:17 by vvaucoul          #+#    #+#              #
#    Updated: 2022/07/20 10:29:23 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include Colors.mk

LIBFT		=	libft.a
NAME		=	lem-in

ifeq ($(shell which clang-11 2>/dev/null),)
CC			=	clang
else
CC			=	clang-11
endif

MATH_FLAG	=	-lm
CFLAGS		=	-g3 -Wall -Wextra #-Werror -ansi / -std=c8

USE_GMON = $(shell ls .use_gmon 2>&1)
ifeq ($(USE_GMON), .use_gmon)
CFLAGS		+= -pg -fno-builtin -g
endif

SRCS_DIR	=	srcs
SRCS		=	$(shell find $(SRCS_DIR) -name '*.c')
OBJS		=	$(SRCS:.c=.o)

%.o: %.c
	@printf "\r$(_LWHITE)Compiling: $(_BOLD)$(_LGREEN)%s$(_END)\n" $<
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

include MLX.mk

$(NAME): ascii $(LIBFT) $(OBJS) $(MLX)
	@printf "\n"
	@$(CC) $(CFLAGS) $(OBJS) $(MATH_FLAG) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@
	@printf "$(_BOLD)$(_BLINK)$(_LGREEN)$(NAME) $(_LWHITE)compiled !\n$(_END)"

$(LIBFT):
	@make -s -C libft all
	@cp libft/42_PCC_LIBFT.a $(LIBFT)

clean:
	@make -s -C libft clean
	@make -s -C $(MLX_PATH) clean > /dev/null 2>&1
	@rm -rf $(MLX_PATH)/obj
	@rm -f $(OBJS)

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME) $(LIBFT)

# Fast RE
fre:
	@rm -f $(OBJS)
	@make -s -C . all

re: 
	@make -s -C . fclean
	@make -s -C libft re
	@make -s -C . all

log-time: 
	@touch .use_gmon
	@make -C . fre
	/usr/bin/time ./$(NAME) < maps/others/maps/valid/1k
	@gprof -s $(NAME) gmon.out
	@gprof $(NAME) gmon.sum > log.out && less log.out && rm gmon.sum log.out gmon.out
	@rm .use_gmon

check-leaks: fre
	/usr/bin/valgrind --leak-check=full  --show-leak-kinds=all ./$(NAME) < maps/test_01.map

generator:
	@make -s -C libft
	@make -s -C generator && cp generator/generator gen

ascii:
	@printf "\n$(_LGREEN)██╗     ███████╗███╗   ███╗      ██╗███╗   ██╗$(_END)\n"
	@printf "$(_LGREEN)██║     ██╔════╝████╗ ████║      ██║████╗  ██║$(_END)\n"
	@printf "$(_LGREEN)██║     █████╗  ██╔████╔██║█████╗██║██╔██╗ ██║$(_END)\n"
	@printf "$(_LGREEN)██║     ██╔══╝  ██║╚██╔╝██║╚════╝██║██║╚██╗██║$(_END)\n"
	@printf "$(_LGREEN)███████╗███████╗██║ ╚═╝ ██║      ██║██║ ╚████║$(_END)\n"
	@printf "$(_LGREEN)╚══════╝╚══════╝╚═╝     ╚═╝      ╚═╝╚═╝  ╚═══╝$(_END)\n"
	@printf "$(_LWHITE)\r\t\t\t   mle-faou & vvaucoul$(_END)\n"

.PHONY: all clean fclean re ascii fre log-time generator check-leaks