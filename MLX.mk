# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MLX.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:09:16 by vvaucoul          #+#    #+#              #
#    Updated: 2022/07/18 01:05:12 by mle-faou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_PATH = MLX42
MLX = $(MLX_PATH)/libmlx42.a
MLX_FLAGS = -ldl -lglfw

$(MLX):
	@printf "$(_LWHITE)Compiling: $(_BOLD)$(_LBLUE)$(MLX_PATH)$(_END)\n"
	@make -s -C $(MLX_PATH) > /dev/null 2>&1