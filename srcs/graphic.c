/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:10:19 by mle-faou          #+#    #+#             */
/*   Updated: 2022/07/19 00:26:20 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/graphic.h"

t_graph g_graph;

int get_turn_count(void)
{
     int count = 0;
    if (g_turns == NULL)
        return (0);
    for (t_turn *tmp = g_turns; tmp; tmp = tmp->next)
        count++;
    return (count);
}

int add_turn(t_ant *ants)
{
    t_turn *new_turn;
    if (!(new_turn = malloc(sizeof(t_turn))))
    {
        printf("Error: malloc failed\n");
        return (1);
    }
    new_turn->id = get_turn_count();
    if (!(new_turn->ants = malloc(sizeof(t_ant) * g_gameinfo.ant_count)))
    {
        printf("Error: malloc failed\n");
        return (1);
    }
    for (int i = 0; i < g_gameinfo.ant_count; i++)
    {
        new_turn->ants[i].id = i;
        new_turn->ants[i].current_room = ants[i].current_room;
    }
    new_turn->next = NULL;
    new_turn->prev = NULL;
    if (g_turns == NULL)
        g_turns = new_turn;
    else
    {
        t_turn *tmp = g_turns;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_turn;
        new_turn->prev = tmp;
    }
    return (0);
}

void free_turns(void)
{
    t_turn *tmp;
    while (g_turns)
    {
        tmp = g_turns;
        g_turns = g_turns->next;
        free(tmp->ants);
        free(tmp);
    }
}

char *get_room_ant_value(t_room *room)
{
    t_turn *tmp = g_turns;
    for (; tmp && tmp->id < g_graph.current_turn; tmp = tmp->next)
        ;
    int ant_count = 0;
    int ant_id = 0;
    for (int i = 0; tmp && i < g_gameinfo.ant_count; i++)
    {
        if (tmp->ants[i].current_room->id == room->id)
        {
            ant_count++;
            ant_id = tmp->ants[i].id;
        }
    }
    if (ant_count > 1)
    {
        char *ant_count_str = ft_itoa(ant_count);
        char *tmp = ft_strjoin("[", ant_count_str);
        free(ant_count_str);
        char *ret = ft_strjoin(tmp, "]");
        free(tmp);
        return (ret);
    }
    else if (ant_count == 1)
        return (ft_itoa(ant_id + 1));
    else
        return (ft_strdup("No ant"));
}

// int exit_mlx(int key, void *param)
// {
//     (void)key;
//     (void)param;
//     // mlx
//     mlx_destroy_image(g_graph.mlx, g_graph.frame);
//     mlx_destroy_window(g_graph.mlx, g_graph.win);
//     mlx_destroy_display(g_graph.mlx);
//     free(g_graph.mlx);
//     // turns
//     t_turn *tmp = g_turns;
//     if (tmp)
//     {
//         while (tmp->next)
//         {
//             free(tmp->ants);
//             tmp = tmp->next;
//             free(tmp->prev);
//         }
//         free(tmp->ants);
//         free(tmp);
//     }
//     // map
//     free_struct();
//     exit(0);
// }

int x_coord_to_pixel(float x)
{
    return ((x - g_graph.left_most) * WINDOW_WIDTH / (g_graph.right_most - g_graph.left_most));
}

int y_coord_to_pixel(float y)
{
    return ((y - g_graph.bottom_most) * WINDOW_HEIGHT / (g_graph.top_most - g_graph.bottom_most));
}

int distance_to_pixel(float distance)
{
    return (distance * WINDOW_WIDTH / (g_graph.right_most - g_graph.left_most));
}

int draw_circle(int x, int y, int radius, int color)
{
    if (radius < 1)
        radius = 1;
    for (int rowIndex = y - radius; rowIndex < y + radius; rowIndex++)
    {
        for (int colIndex = x - radius; colIndex < x + radius; colIndex++)
        {
            if (pow(colIndex - x, 2) + pow(rowIndex - y, 2) <= pow(radius, 2) &&
                colIndex >= 0 && colIndex < WINDOW_WIDTH && rowIndex >= 0 && rowIndex < WINDOW_HEIGHT)
            {
                mlx_put_pixel(g_graph.frame, colIndex, rowIndex, color);
            }
        }
    }
    return (0);
}

void draw_line(int x1, int y1, int x2, int y2, int width)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    while (1)
    {
        draw_circle(x1, y1, width, MLX_WHITE);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void clear_frame(void)
{
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++)
        {
            mlx_put_pixel(g_graph.frame, j, i, MLX_BLACK);
        }
    }
}

int add_mlx_image_t_to_dump(mlx_image_t *img)
{
    int size = 0;
    if (g_graph.string_dump != NULL)
    {
        for (; g_graph.string_dump[size]; size++)
            ;
    }
    mlx_image_t **new = NULL;
    if (!(new = malloc(sizeof(mlx_image_t *) * (size + 2))))
    {
        printf("Error: malloc failed\n");
        return (1);
    }
    for (int i = 0; i < size; i++)
        new[i] = g_graph.string_dump[i];
    new[size] = img;
    new[size + 1] = NULL;
    free(g_graph.string_dump);
    g_graph.string_dump = new;
    return (0);
}

void clear_string_dump(void)
{
    if (g_graph.string_dump)
    {
        for (int i = 0; g_graph.string_dump[i]; i++)
            mlx_delete_image(g_graph.mlx, g_graph.string_dump[i]);
        free(g_graph.string_dump);
    }
    g_graph.string_dump = NULL;
}

int write_text(char *text, int to_free, int x, int y)
{
    int text_len = (int)ft_strlen(text);
    int bg_offset = 3;
    x += bg_offset;
    y += bg_offset;
    for (int y_bg = y - bg_offset; y_bg < y + bg_offset + 20; y_bg++)
    {
        for (int x_bg = x - bg_offset; x_bg < x + bg_offset + text_len * 10; x_bg++)
        {
            mlx_put_pixel(g_graph.frame, x_bg, y_bg, MLX_BLACK);
        }
    }
    add_mlx_image_t_to_dump(mlx_put_string(g_graph.mlx, text, x, y));
    if (to_free)
        free(text);
    return (0);
}

int draw_map(void)
{
    clear_frame();
    clear_string_dump();

    // turn count
    char *turn_str = NULL;
    char *turn_itoa = ft_itoa(g_graph.current_turn);
    if (!(turn_str = ft_strjoin("Turn ", turn_itoa)))
    {
        printf("Error: malloc failed\n");
        return (1);
    }
    free(turn_itoa);
    write_text(turn_str, 1, 0, 0);

    // links
    for (int i = 0; i < get_room_count(); i++)
    {
        for (int j = 0; j < get_room_links_count(i); j++)
        {
            if (g_gameinfo.map[i]->links[j]->id > i)
            {
                int x1 = x_coord_to_pixel(g_gameinfo.map[i]->x);
                int y1 = y_coord_to_pixel(g_gameinfo.map[i]->y);
                int x2 = x_coord_to_pixel(g_gameinfo.map[g_gameinfo.map[i]->links[j]->id]->x);
                int y2 = y_coord_to_pixel(g_gameinfo.map[g_gameinfo.map[i]->links[j]->id]->y);
                int width = distance_to_pixel(g_graph.link_width);
                draw_line(x1, y1, x2, y2, width);
            }
        }
    }

    // rooms
    for (int i = 0; i < get_room_count(); i++)
    {
        // printf("[%s]:%d, %d\n", g_gameinfo.map[i]->name, g_gameinfo.map[i]->x, g_gameinfo.map[i]->y);
        int x_pixel = x_coord_to_pixel(g_gameinfo.map[i]->x);
        int y_pixel = y_coord_to_pixel(g_gameinfo.map[i]->y);
        int color = MLX_WHITE;
        char *ant_value = get_room_ant_value(g_gameinfo.map[i]);
        if (ft_strcmp(ant_value, "No ant"))
        {
            int new_width = distance_to_pixel(g_graph.room_radius * 0.1);
            if (new_width < 1)
                new_width = 1;
            draw_circle(x_pixel, y_pixel, distance_to_pixel(g_graph.room_radius) + new_width, MLX_RED);
        }
        if (get_start_room()->id == g_gameinfo.map[i]->id)
        {
            color = MLX_GREEN;
        }
        else if (get_end_room()->id == g_gameinfo.map[i]->id)
        {
            color = MLX_BLUE;
        }
        draw_circle(x_pixel, y_pixel, distance_to_pixel(g_graph.room_radius), color);
        if (distance_to_pixel(g_graph.room_radius) < 10)
        {
            free(ant_value);
            continue;
        }
        x_pixel -= distance_to_pixel(g_graph.room_radius * 0.5);
        y_pixel -= distance_to_pixel(g_graph.room_radius * 0.5);
        write_text(g_gameinfo.map[i]->name, 0, x_pixel, y_pixel);
        write_text(ant_value, 1, x_pixel, y_pixel + 20);
    }
    return (0);
}

void input(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action != MLX_RELEASE)
        mlx_close_window(param);
    if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
    {
        if (g_graph.current_turn == 0)
            return;
        g_graph.current_turn -= 1;
        draw_map();
    }
    if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
    {
        if (g_graph.current_turn == get_turn_count() - 1)
            return;
        g_graph.current_turn += 1;
        draw_map();
    }
}

int graphic(void)
{
    if (!(g_graph.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "lem-in", false)))
    {
        printf("Error: mlx_init failed\n");
        return (1);
    }
    if (!(g_graph.frame = mlx_new_image(g_graph.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
    {
        printf("Error: mlx_new_image failed\n");
        return (1);
    }
    if (mlx_image_to_window(g_graph.mlx, g_graph.frame, 0, 0) == -1)
    {
        printf("Error: mlx_image_to_window failed\n");
        return (1);
    }
    g_graph.string_dump = NULL;
    g_graph.current_turn = 0;
    g_graph.room_radius = get_smallest_distance() / 4;
    g_graph.link_width = g_graph.room_radius / 8;
    float room_offset = g_graph.room_radius * 2;
    g_graph.left_most = get_left_most_room()->x - room_offset;
    g_graph.right_most = get_right_most_room()->x + room_offset;
    g_graph.top_most = get_top_most_room()->y + room_offset;
    g_graph.bottom_most = get_bottom_most_room()->y - room_offset;

    if (fabs(g_graph.bottom_most - g_graph.top_most) * (16.0 / 9.0) > fabs(g_graph.right_most - g_graph.left_most))
    {
        float ratio_offset = (fabs(g_graph.bottom_most - g_graph.top_most) * (16.0 / 9.0) - fabs(g_graph.right_most - g_graph.left_most)) / 2;
        g_graph.left_most -= ratio_offset;
        g_graph.right_most += ratio_offset;
    }
    else
    {
        float ratio_offset = (fabs(g_graph.right_most - g_graph.left_most) * (9.0 / 16.0) - fabs(g_graph.bottom_most - g_graph.top_most)) / 2;
        g_graph.top_most += ratio_offset;
        g_graph.bottom_most -= ratio_offset;
    }

    draw_map();

    mlx_key_hook(g_graph.mlx, &input, g_graph.mlx);
    mlx_loop(g_graph.mlx);
    mlx_terminate(g_graph.mlx);

    return (0);
}

// PLAN :
// get scale for map
// search largest distance for map size
// map size is largest possible minus a room width on each side
// set rooms size
// search smallest distance for room circle radius
// room circle radius is largest possible with the smallest link being a room size
// draw links (grey)
// draw basic rooms (grey)
// draw start (green)
// draw end (blue)
// draw rooms names (white)
// draw turn count (white)
// draw actions (white)
// draw ants in strat and end (red) -> [X] (number in room)
// draw ants in other rooms (white) -> X (id of the unique ant)
// maybe draw arrows (red)
