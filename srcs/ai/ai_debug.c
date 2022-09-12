/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:04:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 13:02:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>
#include <stdarg.h>

/*******************************************************************************
 *                             DEBUG - NO VERBOSE                              *
 ******************************************************************************/

#if AI_DEBUG_INPUT == 0
void __debug_wait_input(void) {}
#endif

#if AI_VERBOSE == 0
void __debug_print(char *str, ...)
{
    (void)str;
}
void __debug_print_path(EkPath *path)
{
    (void)path;
}
void __debug_print_graph(EkGraph *graph)
{
    (void)graph;
}
void __debug_display_lilo(int *__lilo)
{
    (void)__lilo;
}
void __debug_display_visited(int *__visited)
{
    (void)__visited;
}
void __debug_display_ai_rooms(AiRoom **rooms)
{
    (void)rooms;
}
#endif

/*******************************************************************************
 *                                    DEBUG                                    *
 ******************************************************************************/

#if AI_DEBUG_INPUT == 1
/* Debug wait input */
void __debug_wait_input(void)
{
    if (AI_DEBUG_INPUT == false)
        return;
    char c;

    while (read(1, &c, 1) >= 0)
    {
        if (c == '\n')
            break;
    }
}
#endif

#if AI_VERBOSE == 1
/* Debug print message */
void __debug_print(char *str, ...)
{
    va_list ap;
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap);
}
/* Debug print path */
void __debug_print_path(EkPath *path)
{
    EkRoom *tmp = path->room;

    if (!tmp)
    {
        printf(COLOR_LIGHT_RED "Empty Path !\n" COLOR_RESET);
        return;
    }
    else
        printf(COLOR_LIGHT_CYAN "Path: " COLOR_RESET "[" COLOR_LIGHT_GREEN "%d" COLOR_RESET "] | ", path->id);
    while (tmp)
    {
        printf("[" COLOR_LIGHT_GREEN "%s" COLOR_RESET "]", __room_get_room(tmp->room_ref)->name);
        tmp = tmp->next;
        if (tmp)
        {
            printf(COLOR_LIGHT_CYAN " -> " COLOR_RESET);
        }
    }
    printf("\n");
}

/* Debug print graph */
void __debug_print_graph(EkGraph *graph)
{
    printf(COLOR_LIGHT_GREEN "\nEK GRAPH:\n" COLOR_RESET);
    EkPath *tmp = graph->root_path;

    while (tmp)
    {
        __debug_print_path(tmp);
        tmp = tmp->next;
    }
}

/* Debug print Lilo Stack */
void __debug_display_lilo(int *__lilo)
{
    printf(COLOR_LIGHT_GREEN "\nLILO STACK:\n" COLOR_RESET);
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (__lilo[i] == -1)
            break;
        printf("[" COLOR_LIGHT_CYAN "%d" COLOR_RESET "]-[" COLOR_LIGHT_GREEN "%s" COLOR_RESET "]\n", i, ROOM_NAME(__lilo[i]));
    }
}

/* Debug print rooms visited */
void __debug_display_visited(int *__visited)
{
    printf(COLOR_LIGHT_GREEN "\nVISITED STACK:\n" COLOR_RESET);
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (__visited[i] == -1)
            break;
        printf("[" COLOR_LIGHT_CYAN "%d" COLOR_RESET "]-[" COLOR_LIGHT_GREEN "%s" COLOR_RESET "]\n", i, ROOM_NAME(__visited[i]));
    }
}

/* Debug display ai rooms */
void __debug_display_ai_rooms(AiRoom **rooms)
{
    printf(COLOR_LIGHT_GREEN "\nAI-ROOMS:\n" COLOR_RESET);
    const int room_count = get_room_count();

    for (int i = 0; i < room_count; i++)
    {
        if (AI_ROOM_IS_EMPTY(rooms[i]))
            break;
        printf("[" COLOR_LIGHT_CYAN "%d" COLOR_RESET "]-[" COLOR_LIGHT_GREEN "%s" COLOR_RESET "]-[" COLOR_LIGHT_GREEN "%d" COLOR_RESET "]-", i, ROOM_NAME(rooms[i]->room_ref), rooms[i]->weight);

        AiRoom **links = rooms[i]->links;

        if (links != NULL && links[0] != NULL)
        {
            for (int j = 0; j < room_count; j++)
            {
                if (links[j] == NULL)
                    break;
                else
                {
                    printf("[" COLOR_LIGHT_MAGENTA "%s" COLOR_RESET "]", ROOM_NAME(links[j]->room_ref));
                    if (links[j + 1])
                        printf("->");
                }
            }
        }
        else
            printf("[" COLOR_LIGHT_MAGENTA "%s" COLOR_RESET "]", ("empty"));
        printf("\n");
    }
}
#endif