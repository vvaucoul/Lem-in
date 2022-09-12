/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:36:29 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/07 20:18:07 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>

/*******************************************************************************
 *                  AI ROOMS - (REPLACE LEMIN DEFAULT ROOMS)                   *
 ******************************************************************************/

int __ai_room_init(void)
{
    const int room_count = __room_get_count();

    if (!(g_ai_rooms = (AiRoom **)malloc(sizeof(AiRoom) * room_count)))
        exit(__return_error("AiRoom malloc failed", 1));
    else
    {
        for (int i = 0; i < room_count; i++)
            g_ai_rooms[i] = NULL;
    }
    return (0);
}

AiRoom *__ai_room_create_room(int room_ref, int weight)
{
    AiRoom *__room;

    if (!(__room = (AiRoom *)malloc(sizeof(AiRoom))))
        exit(__return_error("AiRoom malloc failed", 1));
    else
    {
        __room->room_ref = room_ref;
        __room->weight = weight;
        __room->links = NULL;
        return (__room);
    }
}

void __ai_room_push_room(AiRoom *room)
{
    const int room_count = __room_get_count();

    for (int i = 0; i < room_count; i++)
    {
        if (AI_ROOM_IS_EMPTY(g_ai_rooms[i]))
        {
            g_ai_rooms[i] = room;
            return;
        }
    }
}

AiRoom *__ai_room_get_room_by_id(int id)
{
    const int room_count = __room_get_count();

    for (int i = 0; i < room_count; i++)
    {
        if (g_ai_rooms[i]->room_ref == id)
            return (g_ai_rooms[i]);
    }
    return (NULL);
}

AiRoom *__ai_room_get_start_room(void)
{
    int id = __room_get_start_room()->id;
    return (__ai_room_get_room_by_id(id));
}

AiRoom *__ai_room_get_end_room(void)
{
    int id = __room_get_end_room()->id;
    return (__ai_room_get_room_by_id(id));
}

AiRoom *__ai_room_get_ant_room(ANT *ant)
{
    const int __ant_room = ant->current_room->id;

    return (__ai_room_get_room_by_id(__ant_room));
}

int __ai_room_get_links_count(AiRoom *ref)
{
    if (ref && ref->links && ref->links[0])
    {
        int i = 0;

        for (; ref->links[i]; i++)
            ;
        return (i);
    }
    else
        return (0);
}

static void __ai_rooms_fix_links_remove_link(AiRoom *ref, int remove)
{
    const int __nb_links = __ai_room_get_links_count(ref);

    if (__nb_links == 1)
    {
        ref->links[0] = NULL;
        return;
    }

    for (int i = remove; i < __nb_links - 1; i++)
        ref->links[i] = ref->links[i + 1];
    ref->links[__nb_links - 1] = NULL;
}

/* Remove links if links -> links as not better value than current room */
int __ai_rooms_fix_links()
{
    __debug_display_ai_rooms(g_ai_rooms);
    const int room_count = __room_get_count();

    for (int i = 0; i < room_count; i++)
    {
        AiRoom *__current_room = g_ai_rooms[i];
        const int __nb_links = __ai_room_get_links_count(__current_room);
        __debug_print("__current_room: %s\n", __room_get_room(__current_room->room_ref)->name);

        for (int j = 0; j < __nb_links; j++)
        {
            AiRoom *__current_link = __current_room->links[j];
            const int __nb_sub_links = __ai_room_get_links_count(__current_link);
            __debug_print("  __current_link: %s\n", __room_get_room(__current_link->room_ref)->name);

            if (__nb_sub_links == 0)
                continue;

            bool __has_better_value = false;
            for (int k = 0; k < __nb_sub_links; k++)
            {
                AiRoom *__current_sub_link = __current_link->links[k];
                __debug_print("    __current_sub_link: %s\n", __room_get_room(__current_sub_link->room_ref)->name);

                if (__current_sub_link->room_ref == __current_room->room_ref)
                    continue;
                if (__current_sub_link->weight >= __current_room->weight)
                {
                    __has_better_value = true;
                    break;
                }
            }
            if (__has_better_value == false)
            {
                __debug_print(COLOR_LIGHT_RED "Delete link %s\n" COLOR_RESET, __room_get_room(__current_room->links[j]->room_ref)->name);
                __ai_rooms_fix_links_remove_link(__current_room, j);
                // __current_room->links[j] = NULL;
                --i;
                break;
            }
        }
    }
    __debug_display_ai_rooms(g_ai_rooms);
    return (0);
}

int __ai_rooms_update_links()
{
    const int room_count = __room_get_count();
    const int end_room = __room_get_end_room()->id;

    for (int i = 0; i < room_count; i++)
    {
        if (g_ai_rooms[i] == NULL)
            return (1);
        else
        {
            AiRoom *__current = g_ai_rooms[i];

            t_room **links = __room_get_room(__current->room_ref)->links;
            int links_count = __room_get_links_count(__current->room_ref);

            if (__current->room_ref == end_room)
            {
                __current->links = NULL;
                continue;
            }

            if (!(__current->links = (AiRoom **)malloc(sizeof(AiRoom) * (links_count + 1))))
                exit(__return_error("AiRoom links malloc failed", 1));
            else
            {
                for (int j = 0; j < links_count + 1; j++)
                    __current->links[j] = NULL;
            }

            int k = 0;
            for (int j = 0; j < links_count; j++)
            {
                AiRoom *__current_link_ai_room = __ai_room_get_room_by_id(links[j]->id);
                int __room_weight = __current_link_ai_room->weight;

                if (__room_weight < __current->weight)
                    continue;
                __current->links[k] = __current_link_ai_room;
                k++;
            }
        }
    }
    return (0);
}

void __ai_rooms_free(void)
{
    const int room_count = __room_get_count();

    for (int i = 0; i < room_count; i++)
    {
        AiRoom *__current = g_ai_rooms[i];

        if (__current)
        {
            if (__current->links)
            {
                free(__current->links);
                __current->links = NULL;
            }
            free(__current);
            __current = NULL;
        }
        else
            break;
    }
    free(g_ai_rooms);
    g_ai_rooms = NULL;
}