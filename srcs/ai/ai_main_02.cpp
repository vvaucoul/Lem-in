/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_main_02.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:20:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/16 17:30:07 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/old-ai-02.h"
#include <stdarg.h>

ANT *g_ants = NULL;
EK *g_ek = NULL;

/*******************************************************************************
 *                                    DEBUG                                    *
 ******************************************************************************/

static void __debug_print(char *str, ...)
{
    va_list ap;
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap);
}

static void __debug_wait_input(void)
{
    // return;
    char c;
    size_t size = 0;

    while (read(1, &c, 1) >= 0)
    {
        if (c == '\n')
            break;
    }
}

static void __debug_print_ek_path(EK_PATH *__ek_path)
{
    EK_NODE *__ek_node = __ek_path->root;
    if (__ek_node == NULL)
    {
        __debug_print(COLOR_LIGHT_RED "[NULL]" COLOR_RESET "\n");
        return;
    }

    while (__ek_node)
    {
        __debug_print(COLOR_LIGHT_MAGENTA "[%d] " COLOR_RESET, __ek_node->id);
        if (__ek_node->next)
            __debug_print(COLOR_LIGHT_MAGENTA "-> " COLOR_RESET);
        __ek_node = __ek_node->next;
    }
    __debug_print("\n");
}

static void __debug_print_all_ek_path(EK_PATH *__ek_path)
{
    EK_PATH *tmp = __ek_path;

    while (tmp)
    {
        __debug_print_ek_path(tmp);
        tmp = tmp->next;
    }
}

/*******************************************************************************
 *                                    UTILS                                    *
 ******************************************************************************/

static bool __utils_check_end(void)
{
    const int __end_room_id = __room_get_end_room()->id;

    for (int i = 0; i < ANT_COUNT(); i++)
    {
        if (GET_ANT(i).current_room->id != __end_room_id)
            return (false);
    }
    return (true);
}

/*******************************************************************************
 *                                    ANTS                                     *
 ******************************************************************************/

static int __ants_init(void)
{
    __debug_print("- Init ants\n" COLOR_RESET);
    if (!(g_ants = malloc(sizeof(ANT) * ANT_COUNT())))
    {
        __debug_print("- Error: %s\n" COLOR_RESET);
        return (1);
    }
    else
    {
        const t_room *room = __room_get_start_room();
        for (int i = 0; i < ANT_COUNT(); i++)
        {
            g_ants[i].id = i + 1;
            g_ants[i].x = room->x;
            g_ants[i].y = room->y;
            g_ants[i].current_room = (t_room *)room;
        }
    }
    return (0);
}

static void __ants_move_ant(ANT *ant, EK_NODE *node)
{
    const t_room *current_room = __room_get_room(node->id);

    __debug_print("- Move Ant " COLOR_LIGHT_GREEN "#%d" COLOR_RESET " from " COLOR_LIGHT_GREEN "%s" COLOR_RESET " to " COLOR_LIGHT_GREEN "%s" COLOR_RESET "\n" COLOR_RESET,
                  ant->id, ant->current_room->name, current_room->name);
    ant->current_room = (t_room *)current_room;
    ant->x = current_room->x;
    ant->y = current_room->y;
}

static void __ants_free(void)
{
    __debug_print("- Free ants\n" COLOR_RESET);
    free(g_ants);
}

/*******************************************************************************
 *                                  EK UTILS                                   *
 ******************************************************************************/

/* NODES */

static EK_NODE *__ek_node_create_node(EK_NODE *prev, int id, bool flag)
{
    EK_NODE *node = malloc(sizeof(EK_NODE));
    if (!node)
        return (NULL);
    node->prev = prev;
    node->depth = prev ? prev->depth + 1 : 0;
    node->id = id;
    node->flag = flag;
    node->next = NULL;
    __debug_print("\t  - Create " COLOR_YELLOW "node " COLOR_RESET ": " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n" COLOR_RESET, node->id);
    return (node);
}

static void __ek_node_push_path(EK_PATH *path, EK_NODE *node)
{
    if (path->root == NULL)
        path->root = node;
    else
    {
        EK_NODE *tmp = path->root;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }
    path->current = node;
}

static int __ek_node_get_valid_links(EK_PATH *__ek_path, t_room *valid_links[], t_room **links, int count)
{
    bool link_valid = true;
    int j = 0;

    const int __end_room_id = __room_get_end_room()->id;
    for (int i = 0; i < count; i++)
    {
        EK_NODE *tmp = __ek_path->root;
        while (tmp)
        {
            __debug_print("\t  - Check link " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " <-> " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n" COLOR_RESET, tmp->id, links[i]->id);
            const int __current_room_id = __room_get_room(tmp->id)->id;
            if ((tmp->id == links[i]->id && tmp->flag == true) || (__current_room_id == __end_room_id))
            {
                link_valid = false;
                break;
            }
            tmp = tmp->next;
        }
        if (link_valid == true)
        {
            valid_links[j] = links[i];
            j++;
        }
        else
            link_valid = true;
    }
    valid_links[j] = NULL;
    return (j);
}

/* PATH */

static EK_PATH *__ek_path_create_path(int depth)
{
    EK_PATH *path = malloc(sizeof(EK_PATH));
    if (!path)
        return (NULL);
    path->root = NULL;
    path->current = NULL;
    path->next = NULL;
    path->depth = depth;
    return (path);
}

static void __ek_path_push_path(EK *ek, EK_PATH *path)
{
    if (!ek->paths)
    {
        ek->paths = path;
        return;
    }
    EK_PATH *tmp = ek->paths;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = path;
}

static EK_PATH *__ek_path_delete_path(EK_PATH *__ek_path, EK_PATH *__delete_path)
{
    __debug_print(COLOR_LIGHT_YELLOW "Warning: Pruning Path [%d]" COLOR_RESET "\n", __ai_get_last_node(__delete_path)->id);
    printf(COLOR_LIGHT_YELLOW "- Delete: [%d] " COLOR_RESET, __delete_path->depth);
    __debug_print_ek_path(__delete_path);

    if (__ek_path == __delete_path)
    {
        __debug_print(COLOR_LIGHT_YELLOW "Warning: Pruning same path" COLOR_RESET "\n");
        EK_PATH *tmp = __ek_path;
        __ek_path = __ek_path->next;
        // free(tmp);
        return (__ek_path);
    }
    else
    {
        EK_PATH *tmp = __ek_path;
        EK_PATH *prev = NULL;

        while (tmp != NULL && tmp != __delete_path)
        {
            prev = tmp;
            tmp = tmp->next;
        }

        if (tmp == NULL)
            return (__ek_path);
        prev->next = tmp->next;

        free(tmp);
        return (__ek_path);
    }
}

static void __ek_path_push_local_path(EK_PATH *__ek_path, EK_PATH *__new_path)
{
    if (!__ek_path->next)
        __ek_path->next = __new_path;
    else
    {
        EK_PATH *tmp = __ek_path->next;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = __new_path;
    }
}

static void __ek_path_copy_root_till_node(EK_PATH *__ek_path, EK_PATH *__new_ek_path, EK_NODE *__ek_node)
{
    EK_NODE *tmp = __ek_path->root;
    EK_NODE *prev = NULL;

    if (!__ek_node)
    {
        __new_ek_path->root = __ek_path->root;
        __new_ek_path->current = __ek_path->root;
        __new_ek_path->next = NULL;
        return;
    }
    __debug_print("\t  - Copy root till node " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n" COLOR_RESET, __ek_node->id);
    if (tmp == __ek_node)
    {
        __new_ek_path->root = __ek_path->root;
        __new_ek_path->current = __ek_path->root;
        __new_ek_path->next = NULL;
        return;
    }
    while (tmp)
    {
        if (tmp->id == __ek_node->id)
            break;
        EK_NODE *node = __ek_node_create_node(prev, tmp->id, tmp->flag);
        __ek_node_push_path(__new_ek_path, node);
        prev = tmp;
        tmp = tmp->next;
    }
    EK_NODE *node = __ek_node_create_node(prev, tmp->id, tmp->flag);
    __ek_node_push_path(__new_ek_path, node);
}

/* EK */

static int __ek_init_ek(void)
{
    // 1 EK Solver / ANT
    if (!(g_ek = malloc(sizeof(EK) * (ANT_COUNT() + 1))))
        return (1);
    for (int i = 0; i <= ANT_COUNT(); i++)
    {
        g_ek[i].paths = NULL;
        g_ek[i].current_path = NULL;
    }
    return (0);
}

/*******************************************************************************
 *                                 EK SOLVERS                                  *
 ******************************************************************************/

static int __ek_set_best_path(EK_PATH *__ek_path, ANT *ant)
{
    // const EK_NODE *__current_ant_room = __ai_get_node_by_id(__ek_path, ant->current_room->id);
    // const EK_NODE *__next_ant_room = __ai_get_node_by_id(__ek_path, __room_get_room(__current_ant_room->next->id)->id);

    // if (__ai_any_ant_is_in_room(g_ants, __next_ant_room) == true)
    // {
    //     __debug_print(COLOR_LIGHT_YELLOW "Warning: Ant is in room [%d]" COLOR_RESET "\n", __next_ant_room->id);
    //     return (1);
    // }

    __debug_print(COLOR_LIGHT_YELLOW "Warning: Set best path" COLOR_RESET "\n");

    if (GET_EK_PATH(ant->id).best_path == NULL)
    {
        GET_EK_PATH(ant->id).best_path = __ek_path;
        return (0);
    }
    if (__ai_get_last_node(GET_EK_PATH(ant->id).best_path)->depth > __ai_get_last_node(__ek_path)->depth)
    {
        GET_EK_PATH(ant->id).best_path = __ek_path;
        return (0);
    }
    return (1);
}

static int __ek_path_solver(ANT *ant, EK_PATH *__ek_root, EK_PATH *__ek_path, EK_NODE *current_node, const t_room *current_room)
{
    __debug_print_ek_path(__ek_path);
    EK_NODE *node = NULL;

    if (__ai_room_as_been_visited(__ek_path, current_room) == false)
    {
        node = __ek_node_create_node(current_node, current_room->id, true);
        if (!node)
            return (1);
        else
            __ek_node_push_path(__ek_path, node);
        __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Create new node " COLOR_LIGHT_CYAN "[%d]" COLOR_RESET "\n" COLOR_RESET, current_room->id);
    }
    else
    {
        __ek_root = __ek_path_delete_path(__ek_root, __ek_path);
        return (1);
    }

    const EK_NODE *__current_ant_room = __ai_get_node_by_id(__ek_path, __room_get_room(ant->current_room->id)->id);
    const EK_NODE *__next_ant_room = __ai_get_node_by_id(__ek_path, __room_get_room(__current_ant_room->next->id)->id);
    if (__ai_any_ant_is_in_room(g_ants, __next_ant_room) == true)
    {
        __debug_print(COLOR_LIGHT_YELLOW "Warning: Ant is in room [%d]" COLOR_RESET "\n", __next_ant_room->id);
        __debug_print_ek_path(__ek_path);
        // GET_EK_PATH(ant->id).paths = __ek_path_delete_path(GET_EK_PATH(ant->id).paths, __ek_path);
        __ek_root = __ek_path_delete_path(__ek_root, __ek_path);
        __debug_wait_input();
        return (1);
    }

    const t_room *__end_room = __room_get_end_room();
    __debug_print("\t- Is in End Room: " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, __ai_is_end_room(current_room, __end_room));
    if (__ai_is_end_room(current_room, __end_room) == true)
        return (0);

    const int __current_links_count = __room_get_links_count(current_room->id);
    __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Current room has " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " links\n" COLOR_RESET, __current_links_count);

    t_room *valid_links[__current_links_count + 1];
    const int __current_valid_links_count = __ek_node_get_valid_links(__ek_path, valid_links, current_room->links, __current_links_count);

    __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Current room has " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " valid links\n" COLOR_RESET, __current_valid_links_count);

    if (current_node && current_node->depth >= __room_get_count())
    {
        __ek_root = __ek_path_delete_path(__ek_root, __ek_path);
        return (1);
    }
    if (__current_valid_links_count == 0)
    {
        __ek_root = __ek_path_delete_path(__ek_root, __ek_path);
        return (1);
    }
    else if (__current_valid_links_count == 1)
    {
        return (__ek_path_solver(ant, __ek_root, __ek_path, node, valid_links[0]));
    }
    else if (__current_valid_links_count > 1)
    {
        for (int i = 0; i < __current_valid_links_count; i++)
        {
            const t_room *link = __room_get_room(current_room->links[i]->id);
            EK_PATH *__new_ek_path = __ek_path_create_path(__ek_path->depth + 1);
            if (!__new_ek_path)
                return (1);
            else
            {
                __ek_path_copy_root_till_node(__ek_path, __new_ek_path, node);
                __ek_path_push_local_path(__ek_root, __new_ek_path);
                
                __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Create new path " COLOR_LIGHT_CYAN "[%d]" COLOR_RESET "\n" COLOR_RESET, __new_ek_path->depth);
                int ret = __ek_path_solver(ant, __ek_root, __new_ek_path, node, link);
                // __debug_wait_input();

                // if (ret == 0)
                //     return (0);
            }
        }
    }
    // Prune Path -> useless it didn't find a solution
    __ek_root = __ek_path_delete_path(__ek_root, __ek_path);
    return (1);
}

static int __ek_solver(ANT *ant)
{
    const t_room *__current_ant_room = ant->current_room;
    const int __current_links_count = __room_get_links_count(__current_ant_room->id);

    __debug_print("  - Current Room " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " has " COLOR_LIGHT_GREEN "%d" COLOR_RESET " links\n" COLOR_RESET, __current_ant_room->id, __current_links_count);

    EK_PATH *__ek_path = NULL;
    GET_EK_PATH(ant->id).best_path = NULL;
    for (int i = 0; i < __current_links_count; i++)
    {
        __debug_print(COLOR_LIGHT_RED "-- Start Link " COLOR_LIGHT_GREEN "[%d]" COLOR_LIGHT_RED " --\n" COLOR_RESET, i);
        __ek_path = __ek_path_create_path(0);
        if (!__ek_path)
            return (1);
        else
        {
            // If path exist (copy current path)
            if (GET_EK_PATH(ant->id).current_path != NULL)
            {
                // Check solver -> do not solve again
                __debug_print_ek_path(GET_EK_PATH(ant->id).current_path);
                EK_NODE *__current_ant_node = __ai_get_node_by_id(GET_EK_PATH(ant->id).current_path, __current_ant_room->id);
                if (__ai_node_next_node_is_valid(g_ants, __current_ant_node) == true)
                {
                    __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Next node is valid | No need to solve path again\n" COLOR_RESET);
                    GET_EK_PATH(ant->id).best_path = GET_EK_PATH(ant->id).paths;
                    __debug_wait_input();
                    break;
                }
                else
                {
                    __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Next node is invalid | Need to solve path again\n" COLOR_RESET);
                    __debug_wait_input();
                }

                //

                __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " current path exists\n" COLOR_RESET);

                __current_ant_node = __ai_get_node_by_id(GET_EK_PATH(ant->id).paths, __current_ant_room->id);
                __ek_path_copy_root_till_node(GET_EK_PATH(ant->id).paths, __ek_path, __current_ant_node);
                __ek_path_push_path(&GET_EK_PATH(ant->id), __ek_path);

                // Delete tous les autres nodes
                __debug_print_all_ek_path(GET_EK_PATH(ant->id).paths);
                __debug_wait_input();

                EK_PATH *tmp = GET_EK_PATH(ant->id).paths;
                while (tmp && tmp->next)
                {
                    GET_EK_PATH(ant->id).paths = __ek_path_delete_path(GET_EK_PATH(ant->id).paths, tmp);
                    tmp = GET_EK_PATH(ant->id).paths;
                }

                __debug_print_all_ek_path(GET_EK_PATH(ant->id).paths);
                __debug_wait_input();

                // Check if link is valid
                EK_NODE *__current_node = GET_EK_PATH(ant->id).paths->root;
                bool valid = true;

                while (__current_node)
                {
                    if (__current_node->id == __current_ant_room->links[i]->id)
                    {
                        valid = false;
                        break;
                    }
                    __current_node = __current_node->next;
                }
                if (!valid)
                {
                    __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Link " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " is invalid\n" COLOR_RESET, __current_ant_room->links[i]->id);
                    continue;
                }
                else
                {
                    __debug_print("\t- " COLOR_LIGHT_CYAN "Solver:" COLOR_RESET " Link " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " is valid\n" COLOR_RESET, __current_ant_room->links[i]->id);
                }

                __debug_wait_input();
            }
            else
            {
                __ek_path_push_path(&GET_EK_PATH(ant->id), __ek_path);
                EK_NODE *node = __ek_node_create_node(NULL, ant->current_room->id, true);
                __ek_node_push_path(__ek_path, node);
            }
        }

        __debug_print(" - Create path " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " & Push to EK\n" COLOR_RESET, i);

        const t_room *__current_link = __room_get_room(__current_ant_room->links[i]->id);
        if ((__ek_path_solver(ant, GET_EK_PATH(ant->id).paths, __ek_path, NULL, __current_link)) == 0)
        {
            __debug_print(COLOR_LIGHT_GREEN "  - New Shorted Path Found !\n" COLOR_RESET);

            if ((__ek_set_best_path(GET_EK_PATH(ant->id).paths, ant)) == 0)
            {
                __debug_print(COLOR_LIGHT_GREEN "  - New Best Path Found !\n" COLOR_RESET);
            }
            // __debug_print_ek_path(__ek_path);

            // a la place de break, continuer les path et récupérer le meilleur path
            // Pour opti : prune / retirer les path qui ont une depth > au meilleur path courrant
            // break;
            __debug_print_ek_path(__ek_path);
        }
        else
        {
            __debug_print(COLOR_LIGHT_RED "  - No Path Found !\n" COLOR_RESET);
        }
    }

    __debug_print(COLOR_LIGHT_GREEN "\nAll EK Paths Solved: \n" COLOR_RESET);
    if (GET_EK_PATH(ant->id).paths)
        __debug_print_all_ek_path(GET_EK_PATH(ant->id).paths);
    __debug_print(COLOR_LIGHT_GREEN "-- Best Path: \n" COLOR_RESET);
    if (GET_EK_PATH(ant->id).best_path)
    {
        __debug_print_ek_path(GET_EK_PATH(ant->id).best_path);
        GET_EK_PATH(ant->id).current_path = GET_EK_PATH(ant->id).best_path;
        __ants_move_ant(ant, __ai_get_node_by_id(GET_EK_PATH(ant->id).best_path, __current_ant_room->id)->next);
    }

    else
        __debug_print(COLOR_RED "No Best Path Found\n" COLOR_RESET);

    // __ants_move_ant(ant, __best_path->root->next);

    __debug_wait_input(); // tmp
    static int i = 0;
    i++;
    // if (i == 4)
    //     pause();
    return (0);
}

/*******************************************************************************
 *                                    MAIN                                     *
 ******************************************************************************/

int ai_main(void)
{
    __debug_print(COLOR_LIGHT_GREEN "### AI MAIN ###\n" COLOR_RESET);

    if ((__ants_init()) == 1)
        return (1);
    if ((__ek_init_ek()) == 1)
        return (1);

    size_t turn = 0;
    while (__utils_check_end() == false)
    {
        __debug_print(COLOR_LIGHT_RED "\n### TURN [%d] ###\n\n" COLOR_RESET, turn);
        for (int i = 0; i < ANT_COUNT(); i++)
        {
            __debug_print(COLOR_LIGHT_RED "----- Ant " COLOR_LIGHT_CYAN "[%d]" COLOR_RESET COLOR_LIGHT_RED " -----\n" COLOR_RESET, g_ants[i].id);
            if ((__ek_solver(&g_ants[i])) == 1)
                return (1);
        }
        // usleep(100000);
        ++turn;
        // if (turn == 3)
        // break;
    }
    __debug_print(COLOR_LIGHT_GREEN "### PATH SOLVED IN [%ld] turns ###\n" COLOR_RESET, turn);
    return (0);
}

/*
    Objectif de l'algo: OPTIMISATION POUR LES GRANDES MAP

    1. Parser 1 seule fois toute la map pour obtenir une liste chainée de toutes les rooms (avec leurs liens) (recréer la map de matthieu de zéro) - Parser une seule fois chaque noeuds
        1.1 Attribuer un id à chaque room
        1.2 Attribuer une profondeur par rapport à la room de départ

    2. Une fois la map parsée, on peut tracer le chemin adéquat en partant de la fin jusqu'au début

    3. ...

*/