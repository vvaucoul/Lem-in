/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:11:41 by mle-faou          #+#    #+#             */
/*   Updated: 2022/09/08 15:50:47 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "lem_in.h"
#include "ai.h"
#include "ai-utils.h"

#include "../MLX42/include/MLX42/MLX42.h"

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH (WINDOW_HEIGHT * 16 / 9)

#define MLX_WHITE 0xFFFFFFFF
// #define MLX_WHITE 0xC3BFBCFF
// #define MLX_RED 0xFF0000FF
#define MLX_RED 0xFF6065FF
// #define MLX_GREEN 0x00FF00FF
#define MLX_GREEN 0x278550FF
// #define MLX_BLUE 0x0000FFFF
#define MLX_BLUE 0x3B42A8FF
// #define MLX_BLACK 0x000000FF
#define MLX_BLACK 0x24201FFF

typedef struct s_turn t_turn;

struct s_turn
{
    int id;
    t_ant *ants;
    t_turn *next;
    t_turn *prev;
};

extern t_turn *g_turns;

typedef struct s_graph
{
    mlx_t *mlx;
    void *frame;
    mlx_image_t **string_dump;
    int current_turn;
    float left_most;
    float right_most;
    float top_most;
    float bottom_most;
    float room_radius;
    float link_width;
} t_graph;

extern t_graph g_graph;

int graphic(void);
int add_turn(t_ant *ants);
void free_turns(void);

#endif
