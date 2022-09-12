/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 00:28:06 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:42:32 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>

/*******************************************************************************
 *                                  AI SOLVER                                  *
 ******************************************************************************/

static bool __ek_room_already_used(EkRoom *new_room)
{
    const int __nb_ants = g_gameinfo.ant_count;
    const int __end_room = __room_get_end_room()->id;

    for (int i = 0; i < __nb_ants; i++)
    {
        const ANT *__current_ant = &(g_ants[i]);
        if (__current_ant->current_room->id == new_room->room_ref &&
            __current_ant->current_room->id != __end_room)
        {
            __debug_print("Room already used by ant %d\n", __current_ant->id + 1);
            return (true);
        }
    }
    return (false);
}

static int __solver_count = 0;

typedef struct s_ek_solver_path
{
    EkPath *__path;
    int __real_depth;
} t_ek_solver_path;

#define EkSolverPath t_ek_solver_path

static size_t __ek_solver_path_get_nb_path(void)
{
    EkPath *tmp = g_ek_graph->root_path;
    size_t nb_path = 0;

    while (tmp)
    {
        nb_path++;
        tmp = tmp->next;
    }
    return (nb_path);
}

static bool __ek_room_has_ant(EkRoom *room)
{
    for (int i = 0; i < g_gameinfo.ant_count; i++)
    {
        ANT *__current = &(g_ants[i]);
        if (__current->current_room->id == room->room_ref)
            return (true);
    }
    return (false);
}

static int __ek_path_get_depth(EkPath *path)
{
    EkRoom *room = path->room;
    int depth = 0;

    while (room->next)
    {
        depth++;
        room = room->next;
    }
    return (depth);
}

static size_t __ek_solver_path_get_nb_ants_in_path(EkPath *path, AiRoom *current_room)
{
    size_t nb_ants = 0;
    EkRoom *tmp = path->room;

    const int __start_room = __room_get_start_room()->id;
    const int __end_room = __room_get_end_room()->id;

    while (tmp)
    {
        if (tmp->room_ref == current_room->room_ref)
            break;
        tmp = tmp->next;
    }

    while (tmp)
    {
        if (tmp->room_ref == __start_room || tmp->room_ref == __end_room)
        {
            tmp = tmp->next;
            continue;
        }
        const bool __has_ant = __ek_room_has_ant(tmp);
        if (__has_ant == true)
            nb_ants++;
        tmp = tmp->next;
    }
    return (nb_ants);
}

static bool __ek_ant_is_in_path(EkPath *path, ANT *ant)
{
    EkRoom *tmp = path->room;

    while (tmp)
    {
        if (tmp->room_ref == ant->current_room->id)
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

static size_t __ek_solver_distance_from_start(EkPath *path, ANT *ant)
{
    EkRoom *tmp = path->room;
    size_t distance = 0;

    while (tmp)
    {
        if (tmp->room_ref == ant->current_room->id)
            return (distance);
        else
            distance++;
        tmp = tmp->next;
    }
    return (distance);
}

static size_t __ek_solver_nb_ants_in_room(EkRoom *room)
{
    size_t nb_ants = 0;
    for (int i = 0; i < g_gameinfo.ant_count; i++)
    {
        ANT *__current = &(g_ants[i]);
        if (__current->current_room->id == room->room_ref)
            nb_ants++;
    }
    return (nb_ants);
}

static size_t __ek_solver_ants_behind(EkPath *path)
{
    size_t nb_ants = 0;
    EkRoom *tmp = path->room;

    while (tmp)
    {
        if (__ek_room_has_ant(tmp) == true)
            nb_ants += __ek_solver_nb_ants_in_room(tmp);
        tmp = tmp->next;
    }
    return (nb_ants);
}

static EkSolverPath *__ek_solver_path_process_path(ANT *ant)
{
    EkSolverPath *__solver_path = NULL;
    AiRoom *__current_ant_room = __ai_room_get_room_by_id(ant->current_room->id);

    __solver_count = 0;
    if (!(__solver_path = (EkSolverPath *)malloc(sizeof(EkSolverPath) * __ek_solver_path_get_nb_path())))
        exit(__return_error("EkSolverPath malloc failed", 1));
    else
    {
        EkPath *tmp = g_ek_graph->root_path;
        int i = 0;
        while (tmp)
        {
            if (__ek_ant_is_in_path(tmp, ant) == true)
            {
                int __real_depth = 0;

                /* Heuristics */
                __debug_print(COLOR_LIGHT_CYAN "\nHeuristics: \n" COLOR_RESET);
                __debug_print_path(tmp);

                int __heuristic_01 = __ek_path_get_depth(tmp) * 1;
                int __heuristic_02 = __ek_solver_path_get_nb_ants_in_path(tmp, __current_ant_room) * 1;
                int __heuristic_03 = __ek_solver_distance_from_start(tmp, ant) * 1;
                int __heuristic_04 = __ek_solver_ants_behind(tmp) * 1;

                __debug_print(COLOR_LIGHT_CYAN "Heuristic 01: " COLOR_LIGHT_GREEN "%d\n" COLOR_RESET, __heuristic_01);
                __debug_print(COLOR_LIGHT_CYAN "Heuristic 02: " COLOR_LIGHT_GREEN "%d\n" COLOR_RESET, __heuristic_02);
                __debug_print(COLOR_LIGHT_CYAN "Heuristic 03: " COLOR_LIGHT_GREEN "%d\n" COLOR_RESET, __heuristic_03);
                __debug_print(COLOR_LIGHT_CYAN "Heuristic 04: " COLOR_LIGHT_GREEN "%d\n" COLOR_RESET, __heuristic_04);

                __real_depth += __heuristic_01;
                __real_depth += __heuristic_02;
                __real_depth += __heuristic_03;
                __real_depth += __heuristic_04;

                __solver_path[i].__path = tmp;
                __solver_path[i].__real_depth = __real_depth;
                i++;
                __solver_count++;
            }
            tmp = tmp->next;
        }
    }
    return (__solver_path);
}

static void __ek_remove_index(EkSolverPath *__solver, int index)
{
    for (int i = index; i < __solver_count - 1; i++)
    {
        __solver[i] = __solver[i + 1];
    }
    __solver_count--;
}

int __ek_solver(ANT *ant)
{
    __debug_print(COLOR_LIGHT_CYAN "\n###########\n" COLOR_RESET);
    __debug_print(COLOR_LIGHT_CYAN "# ANT [%d] #\n" COLOR_RESET, ant->id + 1);
    __debug_print(COLOR_LIGHT_CYAN "###########\n\n" COLOR_RESET);

    EkSolverPath *__solver = __ek_solver_path_process_path(ant);

    for (int i = 0; i < __solver_count; i++)
    {
        __debug_print(COLOR_LIGHT_CYAN "Path [%d]\n" COLOR_RESET, i);
        __debug_print_path(__solver[i].__path);
        __debug_print(COLOR_LIGHT_CYAN "- Depth: " COLOR_LIGHT_GREEN "%d\n" COLOR_RESET, __solver[i].__real_depth);
    }

    int __previous_best_path_depth = -1;

    for (int __loop = 0; __loop < __solver_count; __loop++)
    {
        EkPath *__best_path = NULL;
        int __best_path_depth = 0;
        int __best_path_index = 0;
        for (int i = 0; i < __solver_count; i++)
        {
            if (__best_path == NULL)
            {
                __best_path = __solver[i].__path;
                __best_path_depth = __solver[i].__real_depth;
                __best_path_index = i;
                continue;
            }
            else if (__solver[i].__real_depth < __best_path_depth && __solver[i].__real_depth >= __previous_best_path_depth)
            {
                __best_path = __solver[i].__path;
                __best_path_depth = __solver[i].__real_depth;
                __best_path_index = i;
            }
        }

        __previous_best_path_depth = __best_path_depth;

        __debug_print(COLOR_LIGHT_CYAN "Best path:\n" COLOR_RESET);
        __debug_print_path(__best_path);

        AiRoom *__current_ai_room = __ai_room_get_ant_room(ant);
        EkRoom *__next_room = NULL;
        EkRoom *__tmp = __best_path->room;

        while (__tmp)
        {
            if (__tmp->room_ref == __current_ai_room->room_ref)
            {
                __next_room = __tmp->next;
                break;
            }
            __tmp = __tmp->next;
        }
        if (__next_room && __ek_room_already_used(__next_room) == true)
            __next_room = NULL;

        if (__next_room == NULL)
        {
            __debug_print(COLOR_LIGHT_RED "No best next room !\n" COLOR_RESET);
        }
        else
        {
            __debug_print("- " COLOR_LIGHT_CYAN "Best Room:" COLOR_RESET " [" COLOR_LIGHT_GREEN "%s" COLOR_RESET "]\n", ROOM_NAME(__next_room->room_ref));
            ant->current_room = __room_get_room(__next_room->room_ref);
            printf("L%d-%s ", ant->id + 1, ROOM_NAME(ant->current_room->id));
            ant->moved = true;
            free(__solver);
            return (0);
        }
        __ek_remove_index(__solver, __best_path_index);
    }
    __debug_print(COLOR_LIGHT_RED "Error: No Path found !\n" COLOR_RESET);
    free(__solver);
    return (0);
}