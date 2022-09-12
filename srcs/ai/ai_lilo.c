/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_lilo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:40:37 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/07 20:23:45 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>

/*******************************************************************************
 *                  AI LILO STACK - LAST IN LAST OUT - ROOMS                   *
 ******************************************************************************/

int __lilo_init(void)
{
    const int room_count = get_room_count();
    if (!(g_lilo_stack = malloc(sizeof(int) * room_count)))
        exit(__return_error("LiloStack malloc failed", 1));
    if (!(g_visited_rooms = malloc(sizeof(int) * room_count)))
        exit(__return_error("VisitedRooms malloc failed", 1));
    for (int i = 0; i < room_count; i++)
    {
        g_lilo_stack[i] = -1;
        g_visited_rooms[i] = -1;
    }
    return (0);
}

void __lilo_free(void)
{
    if (g_lilo_stack != NULL)
    {
        free(g_lilo_stack);
        g_lilo_stack = NULL;
    }
    if (g_visited_rooms != NULL)
    {
        free(g_visited_rooms);
        g_visited_rooms = NULL;
    }
}

int __lilo_add_room(int room_id)
{
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (g_lilo_stack[i] == -1)
        {
            g_lilo_stack[i] = room_id;
            return (0);
        }
    }
    return (1);
}

int __lilo_remove_room(int room_id)
{
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (g_lilo_stack[i] == room_id)
        {
            g_lilo_stack[i] = -1;
            int j = i;
            for (; j < room_count - 1; j++)
                g_lilo_stack[j] = g_lilo_stack[j + 1];
            g_lilo_stack[j] = -1;
            return (0);
        }
    }
    return (1);
}

int __lilo_add_visited_room(int room_id)
{
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (g_visited_rooms[i] == -1)
        {
            g_visited_rooms[i] = room_id;
            return (0);
        }
    }
    return (1);
}

bool __lilo_room_as_been_visited(int room_id)
{
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (g_visited_rooms[i] == room_id)
            return (true);
    }
    return (false);
}

int *__lilo_get_instance(void)
{
    int *instance_lilo_stack = NULL;
    const int room_count = get_room_count();

    if (!(instance_lilo_stack = malloc(sizeof(int) * room_count)))
        exit(__return_error("LiloStack malloc failed", 1));
    for (int i = 0; i < room_count; i++)
        instance_lilo_stack[i] = g_lilo_stack[i];
    return (instance_lilo_stack);
}

void __lilo_free_instance(int *instance_lilo_stack)
{
    if (instance_lilo_stack != NULL)
    {
        free(instance_lilo_stack);
        instance_lilo_stack = NULL;
    }
}
