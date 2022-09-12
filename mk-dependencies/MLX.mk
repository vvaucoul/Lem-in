# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MLX.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 16:09:16 by vvaucoul          #+#    #+#              #
#    Updated: 2022/09/08 11:33:32 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_PATH = MLX42
MLX = $(MLX_PATH)/libmlx42.a
MLX_FLAGS = -ldl -lglfw

$(MLX):
	@printf "$(_LWHITE)Compiling: $(_BOLD)$(_LBLUE)$(MLX_PATH)$(_END)\n"
	@make -s -C $(MLX_PATH) > /dev/null 2>&1

mlx: $(MLX)

mlx-clean:
	@make -s -C $(MLX_PATH) clean > /dev/null 2>&1
	@rm -rf $(MLX_PATH)/obj $(MLX)

.PHONY: mlx mlx-clean