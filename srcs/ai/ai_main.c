/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:59:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:33:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>
#include <graphic.h>

ANT *g_ants = NULL; // Lem-In Ants

EkGraph *g_ek_graph = NULL; // Edmond Karp graph

int *g_lilo_stack = NULL;    // Store Next Rooms to Process
int *g_visited_rooms = NULL; // Store All Visited Rooms

AiRoom **g_ai_rooms = NULL; // AI Rooms / Replace Default rooms

static int __exit_free(void)
{
    __ants_free();
    __debug_print("- Free " COLOR_GREEN "Ants\n" COLOR_RESET);
    __lilo_free();
    __debug_print("- Free " COLOR_GREEN "Lilo\n" COLOR_RESET);
    __ai_rooms_free();
    __debug_print("- Free " COLOR_GREEN "AI ROoms\n" COLOR_RESET);

    __ek_free(g_ek_graph);
    __debug_print("- Free " COLOR_GREEN "EK Graph\n" COLOR_RESET);
    return (0);
}

/*******************************************************************************
 *                                 AI - GRAPH                                  *
 ******************************************************************************/

static bool __ai_process_room_has_been_added(EkPath *current_path, EkRoom *room)
{
    if (!current_path)
        return (false);
    else if (!room)
        return (false);
    else
    {
        EkRoom *tmp = current_path->room;

        if (!tmp)
            return (false);
        else
        {
            while (tmp->next)
            {
                if (tmp->room_ref == room->room_ref)
                    return (true);
                tmp = tmp->next;
            }
        }
    }
    return (false);
}

bool __end_room_as_been_reached = false;

static void ai_process_graph_recursif(AiRoom *current_room, EkPath *current_path)
{
    static int __depth = -1;
    const int __current_room_links = __ai_room_get_links_count(current_room);

    /* Increase Recursivity Depth */    
    __depth++;

    /* Secure */
    if (__depth > RECURSIVE_MAX_DEPTH && __end_room_as_been_reached == true)
        return;
    if (__end_room_as_been_reached == false && __room_get_room(current_room->room_ref)->type == END)
        __end_room_as_been_reached = true;

    if (__current_room_links == 1)
    {
        /* Continue on the Same Path */
        const int __link_id = current_room->links[0]->room_ref;
        AiRoom *__current_link = __ai_room_get_room_by_id(__link_id);
        EkRoom *__current_ek_room = __ek_create_room(__link_id, current_room->weight + 1);

        if (__ai_process_room_has_been_added(current_path, __current_ek_room) == true)
        {
            free(__current_ek_room);
            return;
        }

        __ek_graph_push_room(current_path, __current_ek_room);
        __debug_print_path(current_path);
        ai_process_graph_recursif(__current_link, current_path);
    }
    else if (__current_room_links > 1)
    {
        /* Create new Path for each links */
        for (int i = 0; i < __current_room_links; i++)
        {
            const int __link_id = current_room->links[i]->room_ref;
            AiRoom *__current_link = __ai_room_get_room_by_id(__link_id);
            EkRoom *__current_ek_room = __ek_create_room(__link_id, current_room->weight + 1);

            if (__ai_process_room_has_been_added(current_path, __current_ek_room) == true)
            {
                free(__current_ek_room);
                return;
            }

            EkPath *__new_path = __ek_create_path(__current_ek_room);
            __new_path = __ek_append_path(current_path, __new_path);
            __ek_graph_push_path(g_ek_graph, __new_path);
            __debug_print_path(__new_path);
            ai_process_graph_recursif(__current_link, __new_path);
        }
    }
    else
    {
        return;
    }
    return;
}

static void ai_process_graph(void)
{
    AiRoom *__start_room = __ai_room_get_start_room();
    EkRoom *__ek_start_room = __ek_create_room(__start_room->room_ref, 0);
    EkPath *__start_path = __ek_create_path(__ek_start_room);

    __ek_graph_push_path(g_ek_graph, __start_path);
    __debug_print_graph(g_ek_graph);
    ai_process_graph_recursif(__start_room, __start_path);
    __debug_print_graph(g_ek_graph);
    __ek_graph_prune_paths(g_ek_graph);
    __debug_print_graph(g_ek_graph);
}

/*******************************************************************************
 *                                AI - MAPPING                                 *
 ******************************************************************************/

static void __ai_graph_process_lilo_rooms(int weight)
{
    const int room_count = get_room_count();
    int *instance_lilo_stack = __lilo_get_instance();

    __debug_display_lilo(g_lilo_stack);
    __debug_display_visited(g_visited_rooms);

    for (int i = 0; i < room_count; i++)
    {
        if (instance_lilo_stack[i] == -1)
            break;
        else
        {
            AiRoom *__current_room = __ai_room_create_room(instance_lilo_stack[i], weight);
            __ai_room_push_room(__current_room);

            t_room *current_room = __room_get_room(instance_lilo_stack[i]);
            t_room **links = current_room->links;
            int links_count = __room_get_links_count(current_room->id);

            for (int j = 0; j < links_count; j++)
            {
                if (__lilo_room_as_been_visited(links[j]->id) == false)
                {
                    __lilo_add_room(links[j]->id);
                    __lilo_add_visited_room(links[j]->id);
                }
            }
            __lilo_remove_room(instance_lilo_stack[i]);
        }
    }
    __debug_display_ai_rooms(g_ai_rooms);
    __lilo_free_instance(instance_lilo_stack);
    if (LILO_STACK_IS_EMPTY())
        return;
    else
        __ai_graph_process_lilo_rooms(weight + 1);
}

static void ai_process_mapping(void)
{
    const t_room *start_room = __room_get_start_room();
    __lilo_add_room(start_room->id);
    __lilo_add_visited_room(start_room->id);

    __ai_graph_process_lilo_rooms(0);
    __ai_rooms_update_links();
    __debug_print(COLOR_LIGHT_CYAN "\n[AI ROOMS]" COLOR_RESET " - " COLOR_LIGHT_GREEN "FIX LINKS\n" COLOR_RESET);
    __ai_rooms_fix_links();
    __debug_display_ai_rooms(g_ai_rooms);
}

/*******************************************************************************
 *                                   AI MAIN                                   *
 ******************************************************************************/

int ai_main(void)
{
    __debug_print(COLOR_LIGHT_GREEN "\n\n### IA ###\n\n" COLOR_RESET);
    __debug_print("- Init " COLOR_GREEN "Ants\n" COLOR_RESET);
    printf("\n");

    /* INIT */
    __ants_init();
    __ai_room_init();
    __debug_print("- Init " COLOR_GREEN "AI Rooms\n" COLOR_RESET);
    __lilo_init();
    __debug_print("- Init " COLOR_GREEN "LILO Stack\n" COLOR_RESET);

    g_ek_graph = __ek_create_graph();

    /* Graph Algo */
    ai_process_mapping();
    __debug_print(COLOR_LIGHT_CYAN "\n##################\n" COLOR_RESET);
    __debug_print(COLOR_LIGHT_CYAN "# AI Map Created #\n" COLOR_RESET);
    __debug_print(COLOR_LIGHT_CYAN "##################\n\n" COLOR_RESET);

    ai_process_graph();
    __debug_print(COLOR_LIGHT_CYAN "\n#################\n" COLOR_RESET);
    __debug_print(COLOR_LIGHT_CYAN "# GRAPH CREATED #\n" COLOR_RESET);
    __debug_print(COLOR_LIGHT_CYAN "#################\n\n" COLOR_RESET);

    const int __nb_ants = g_gameinfo.ant_count;
    const int __start_room = __room_get_start_room()->id;
    const int __end_room = __room_get_end_room()->id;
    int __turn = 0;

    bool __exit_loop = false;
    while (__utils_check_end() == false)
    {
        __debug_print(COLOR_LIGHT_WHITE "\n###############\n" COLOR_RESET);
        __debug_print(COLOR_LIGHT_WHITE "# TURN %d #\n" COLOR_RESET, __turn);
        __debug_print(COLOR_LIGHT_WHITE "###############\n\n" COLOR_RESET);
        __exit_loop = false;
        for (int __loop = 0; __loop < 2; __loop++)
        {
            if (__exit_loop == true)
                break;
            for (int i = 0; i < __nb_ants; i++)
            {
                if (g_ants[i].moved == false && g_ants[i].current_room->id != __end_room)
                    __ek_solver(&g_ants[i]);
                if (g_ants[i].moved == false && g_ants[i].current_room->id == __start_room)
                {
                    __exit_loop = true;
                    break;
                }
            }
        }
        for (int i = 0; i < __nb_ants; i++)
        {
            g_ants[i].moved = false;
        }
        printf("\n");
        add_turn(g_ants);
        ++__turn;
    }
    __debug_print("Done in [" COLOR_LIGHT_GREEN "%d" COLOR_RESET "] turns\n", __turn);
    return (__exit_free());
}