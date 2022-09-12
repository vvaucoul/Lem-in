# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 14:56:17 by vvaucoul          #+#    #+#              #
#    Updated: 2022/09/09 13:16:19 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk-dependencies/Colors.mk

LIBFT		=	libft.a
NAME		=	lem-in

ifeq ($(shell which clang-11 2>/dev/null),)
CC			=	clang
else
CC			=	clang-11
endif

MATH_FLAG	=	-lm
CFLAGS		=	-g3 -Wall -Wextra -Werror

USE_GMON = $(shell ls .use_gmon 2>&1)
ifeq ($(USE_GMON), .use_gmon)
CFLAGS		+= -pg -fno-builtin -g
endif

INCLUDES	=	-I./includes

SRCS_DIR	=	srcs
OBJS_DIR	=	objs

SRCS		=	$(shell find $(SRCS_DIR) -name '*.c')
OBJS		=	$(SRCS:.c=.o)
DEPENDS		=	$(OBJS:.o=.d)

%.o: %.c
	@printf "\r$(_CLEAR_LINE)$(_LWHITE)Compiling: $(_BOLD)$(_LGREEN)%s$(_END)\n" $<
	@$(CC) $(INCLUDES) $(CFLAGS) -MD -c $< -o $@

all: $(NAME)

include mk-dependencies/MLX.mk

$(NAME): ascii $(LIBFT) $(OBJS) $(MLX)
	@printf "\n"
	@$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(MATH_FLAG) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@
	@printf "$(_BOLD)$(_BLINK)$(_LGREEN)$(NAME) $(_LWHITE)compiled !\n$(_END)"

$(LIBFT):
	@make -s -C libft all
	@cp libft/42_PCC_LIBFT.a $(LIBFT)

clean:
	@make -s -C libft clean
	@make -s -C . mlx-clean > /dev/null 2>&1
	@rm -f $(OBJS) $(DEPENDS)

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME) $(LIBFT)
	@rm -rf mlx

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
	/usr/bin/time ./$(NAME) < maps/others/maps/valid/6k
	@gprof -s $(NAME) gmon.out
	@gprof $(NAME) gmon.sum > log.out && less log.out && rm gmon.sum log.out gmon.out
	@rm .use_gmon

check-leaks: fre
	@/usr/bin/valgrind --leak-check=full  --show-leak-kinds=all ./$(NAME) < maps/test_01.map
	@/usr/bin/valgrind --leak-check=full  --show-leak-kinds=all ./$(NAME) < maps/basic.map
	@/usr/bin/valgrind --leak-check=full  --show-leak-kinds=all ./$(NAME) < maps/sujet1.map
	@/usr/bin/valgrind --leak-check=full  --show-leak-kinds=all ./$(NAME) < maps/big_map.map

check:
	@sh ./unit_tests.sh

check-maps:
	@sh ./test_all_maps.sh maps
	@sh ./test_all_maps.sh maps/others/maps/valid
	@sh ./test_all_maps.sh maps/others/maps/invalid
	@sh ./test_all_maps.sh maps/others/maps/maps2
	@sh ./test_all_maps.sh maps/others/maps/valid/big
	@sh ./test_all_maps.sh maps/others/maps/valid/big_sup

install-python:
	@printf "$(_BOLD)$(_LWHITE)Installing python module...\n$(_END)"
	@sh ./install_python.sh

help:
	@printf "$(_LWHITE)Program:$(_END)\n"
	@printf "\t$(_LWHITE)$(NAME)$(_END)\n"
	@printf "\n$(_LWHITE)Usage:$(_END)\n"
	@printf "\t$(_LWHITE)make$(_END)\n"
	@printf "\t$(_LWHITE)make re$(_END)\n"
	@printf "\t$(_LWHITE)make fre$(_END)\n"
	@printf "\t$(_LWHITE)make clean$(_END)\n"
	@printf "\t$(_LWHITE)make fclean$(_END)\n"
	@printf "\t$(_LWHITE)make mlx$(_END)\n"
	@printf "\t$(_LWHITE)make mlx-clean$(_END)\n"
	@printf "\n$(_LWHITE)Targets:$(_END)\n"
	@printf "\t$(_LWHITE)all$(_END)$(_DIM) - compile project\n$(_END)"
	@printf "\t$(_LWHITE)clean$(_END)$(_DIM) - clean $(_GREEN)OBJS$(_END)\n$(_END)"
	@printf "\t$(_LWHITE)fclean$(_END)$(_DIM) - clean entire project\n$(_END)"
	@printf "\t$(_LWHITE)re$(_END)$(_DIM) - recompile project\n$(_END)"
	@printf "\t$(_LWHITE)fre$(_END)$(_DIM) - recompile lem-in only\n$(_END)"
	@printf "\t$(_LWHITE)log-time$(_END)$(_DIM) - check functions times with $(_GREEN)GMON$(_END)\n$(_END)"
	@printf "\t$(_LWHITE)check-leaks$(_END)$(_DIM) - check leaks with $(_GREEN)Valgrind$(_END)\n$(_END)"
	@printf "\t$(_LWHITE)check$(_END)$(_DIM) - start unit tests\n$(_END)"
	@printf "\t$(_LWHITE)check-maps$(_END)$(_DIM) - start maps tests\n$(_END)"
	@printf "\t$(_LWHITE)install-python$(_END)$(_DIM) - install python3 module\n$(_END)"
	@printf "\t$(_LWHITE)help$(_END)$(_DIM) - display this help\n$(_END)"
	@printf "\n$(_LWHITE)Flags:$(_END)\n"
	@printf "\t$(_LWHITE)GCC:  $(CFLAGS)$(_END)\n"
	@printf "\t$(_LWHITE)MATH: $(MATH_FLAG)$(_END)\n"
	@printf "\t$(_LWHITE)MLX:  $(MLX_FLAGS)$(_END)\n"
	@printf "\t$(_LWHITE)GMON: -pg -fno-builtin -g$(_END)\n"

ascii:
	@printf "\n$(_LGREEN)██╗     ███████╗███╗   ███╗      ██╗███╗   ██╗$(_END)\n"
	@printf "$(_LGREEN)██║     ██╔════╝████╗ ████║      ██║████╗  ██║$(_END)\n"
	@printf "$(_LGREEN)██║     █████╗  ██╔████╔██║█████╗██║██╔██╗ ██║$(_END)\n"
	@printf "$(_LGREEN)██║     ██╔══╝  ██║╚██╔╝██║╚════╝██║██║╚██╗██║$(_END)\n"
	@printf "$(_LGREEN)███████╗███████╗██║ ╚═╝ ██║      ██║██║ ╚████║$(_END)\n"
	@printf "$(_LGREEN)╚══════╝╚══════╝╚═╝     ╚═╝      ╚═╝╚═╝  ╚═══╝$(_END)\n"
	@printf "$(_LWHITE)\r\t\t\t   mle-faou & vvaucoul$(_END)\n\n"

-include $(DEPENDS)

.PHONY: all clean fclean re ascii fre log-time check-leaks check check-maps help install-python