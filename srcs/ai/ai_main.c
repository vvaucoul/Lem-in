/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:29:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/21 13:03:11 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ai.h"
#include "../../includes/graphic.h"
#include <stdarg.h>

ANT *g_ants;
EK g_ek;

/*******************************************************************************
 *                                    DEBUG                                    *
 ******************************************************************************/

static void __debug_print(char *str, ...)
{
    if (AI_VERBOSE == false)
        return;
    va_list ap;
    va_start(ap, str);
    vprintf(str, ap);
    va_end(ap);
}

static void __debug_wait_input(void)
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

static void __debug_print_path(EK_PATH *path)
{
    t_ek_node *node;

    node = path->root;
    while (node)
    {
        const char *name = __room_get_room(node->id)->name;
        __debug_print(COLOR_LIGHT_GREEN "[%s, %d, %d] " COLOR_RESET, name, node->depth, node->value);
        if (node->next)
            __debug_print("-> ");
        node = node->next;
    }
    __debug_print("\n");
}

static void __debug_print_all_paths(EK_PATH *__root)
{
    EK_PATH *path;
    int i = 0;

    path = __root;
    if (!path)
    {
        __debug_print(COLOR_LIGHT_RED "No path found\n" COLOR_RESET);
        return;
    }
    while (path)
    {
        const int __path_length = path->length;
        __debug_print("Path: [%d -> %d]: ", i, __path_length);
        __debug_print_path(path);
        path = path->next;
        i++;
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
    if (!(g_ants = malloc(sizeof(ANT) * ANT_COUNT())))
        return (-1);
    for (int i = 0; i < ANT_COUNT(); i++)
    {
        const int x = __room_get_start_room()->x;
        const int y = __room_get_start_room()->y;

        GET_ANT(i).id = i;
        GET_ANT(i).x = x;
        GET_ANT(i).y = y;
        GET_ANT(i).moved = false;
        GET_ANT(i).current_room = __room_get_start_room();
    }
    return (0);
}

static int __ants_free(void)
{
    if (g_ants)
    {
        free(g_ants);
        g_ants = NULL;
    }
    return (0);
}

/*******************************************************************************
 *                                  EK UTILS                                   *
 ******************************************************************************/

int __nb_path = 0;
int __nb_path_success = 0;

static EK_NODE *__ek_create_node(EK_NODE *prev, int room_id)
{
    EK_NODE *node = malloc(sizeof(EK_NODE));

    if (!node)
        return (NULL);
    else
    {
        __debug_print("  - Create new node: %d\n", room_id);
        node->parent = prev;
        node->next = NULL;
        node->depth = prev ? prev->depth + 1 : 0;
        node->id = room_id;
        node->value = node->depth;
        return (node);
    }
}

static int __ek_push_node(EK_PATH *ek_path, EK_NODE *new_node)
{
    __debug_print("Push node: %d\n", new_node->id);
    if (ek_path == NULL || new_node == NULL)
        return (1);
    if (ek_path->root == NULL)
        ek_path->root = new_node;
    else
    {
        EK_NODE *tmp = ek_path->root;

        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
    ek_path->length++;
    return (0);
}

// static int __ek_delete_node(EK_PATH *__ek_root, EK_NODE *delete)
// {
//     EK_NODE *tmp = __ek_root->root;

//     if (__ek_root == NULL || delete == NULL)
//         return (1);
//     if (tmp == delete)
//     {
//         tmp = tmp->next;
//         free(delete);
//         return (0);
//     }
//     while (tmp->next && tmp->next != delete)
//         tmp = tmp->next;
//     if (tmp->next == NULL)
//         return (1);
//     tmp->next = tmp->next->next;
//     free(delete);
//     return (0);
// }

static EK_PATH *__ek_create_path(EK_PATH *prev)
{
    EK_PATH *path = malloc(sizeof(EK_PATH));

    if (!path)
        return (NULL);
    else
    {
        path->root = NULL;
        path->next = NULL;
        path->depth = prev ? prev->depth + 1 : 0;
        path->length = 0;
        path->prev = prev;
        return (path);
    }
}

static EK_PATH *__ek_push_path(EK_PATH *root, EK_PATH *path)
{
    __debug_print("Push path: %d\n", path->depth);
    __nb_path++;
    if (path == NULL)
        return (root);
    if (root == NULL)
    {
        __debug_print("  - Assign root path\n");
        root = path;
        return (root);
    }
    EK_PATH *tmp = root;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = path;
    return (root);
}

static int __ek_delete_path(EK_PATH *root, EK_PATH *delete)
{
    if (root == NULL || delete == NULL)
        return (-1);
    __nb_path--;
    __debug_print(COLOR_LIGHT_YELLOW "Pruning path: %p\n" COLOR_RESET, delete);
    if (root == delete)
    {
        EK_PATH *tmp = root->next;
        EK_NODE *tmp_node = root->root;
        while (tmp_node)
        {
            EK_NODE *tmp_node_next = tmp_node->next;
            free(tmp_node);
            tmp_node = tmp_node_next;
        }
        root = tmp;
        return (0);
    }
    EK_PATH *tmp = root;
    while (tmp->next && tmp->next != delete)
        tmp = tmp->next;
    if (tmp->next == delete)
    {
        tmp->next = tmp->next->next;
        EK_NODE *tmp_node = delete->root;
        while (tmp_node)
        {
            EK_NODE *tmp_node_next = tmp_node->next;
            free(tmp_node);
            tmp_node = tmp_node_next;
        }
        free(delete);
        delete = NULL;
    }
    return (0);
}

static int __ek_copy_path(EK_PATH *dest, EK_PATH *src, EK_NODE *till_node)
{
    if (dest == NULL || src == NULL)
        return (-1);
    if (src->root == NULL)
        return (-1);

    EK_NODE *node = src->root;
    EK_NODE *prev = NULL;
    while (node)
    {
        if (__ek_push_node(dest, __ek_create_node(prev, node->id)))
            return (-1);
        if (node == till_node)
            break;
        prev = node;
        node = node->next;
    }
    return (0);
}

static int __ek_init_ek(void)
{
    g_ek.paths = NULL;
    return (0);
}

// static int __ek_link_is_know(EK_PATH *path, int room_id)
// {
//     EK_NODE *node = path->root;

//     while (node)
//     {
//         if (node->id == room_id)
//             return (true);
//         node = node->next;
//     }
//     return (false);
// }

static int __ek_get_valid_links(EK_PATH *path, t_room *valid_links[], int __links_count, t_room **links)
{
    if (links == NULL)
        return (0);
    if (path->root == NULL)
        return (0);
    ft_bzero(valid_links, sizeof(t_room *) * __links_count + 1);

    bool __valid = true;
    int i = 0;
    int j = 0;
    const int __end_room_id = __room_get_end_room()->id;
    for (j = 0; j < __links_count; j++)
    {
        EK_NODE *node = path->root;
        while (node)
        {
            __debug_print("  - Check link: %d <-> %d\n", node->id, links[j]->id);
            const int __current_room_id = __room_get_room(node->id)->id;
            if ((node->id == links[j]->id) || (__current_room_id == __end_room_id))
            {
                __valid = false;
                break;
            }
            node = node->next;
        }
        if (__valid == true)
        {
            __debug_print("  - Push link: %d index: %d\n", links[j]->id, i);
            valid_links[i] = links[j];
            i++;
        }
        else
            __valid = true;
    }
    valid_links[i] = NULL;
    return (i);
}

static bool __ek_ant_is_in_node(ANT *ants, EK_NODE *node)
{
    const int __end_room_id = __room_get_end_room()->id;
    for (int i = 0; i < ANT_COUNT(); i++)
    {
        if (ants[i].current_room->id == node->id && node->id != __end_room_id)
            return (true);
    }
    return (false);
}

static int __ek_max_branch_stuck(int __nb_branch, int __path_found)
{
    (void)__nb_branch;
    static int __current_path_found = 0;
    static int __nb_turn = 0;

    __debug_print("Current nb path: %d\n", __current_path_found);
    __debug_print("Nb turn: %d\n", __nb_turn);
    if (__path_found == 0)
        return (false);
    if (__path_found > __current_path_found)
    {
        __current_path_found = __path_found;
        __nb_turn = 0;
    }
    else if (__path_found == __current_path_found)
        __nb_turn++;
    if (__nb_turn > MAX_BRANCH_STUCK)
        return (true);
    return (false);
}

static int __ek_max_branch()
{
    const int __links_start_count = __room_get_links_count(__room_get_start_room()->id);
    const int __links_end_count = __room_get_links_count(__room_get_end_room()->id);

    __debug_print("- __links_start_count: " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", __links_start_count);
    __debug_print("- __links_end_count: " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", __links_end_count);
    __debug_print("- Path count: " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", __nb_path);
    __debug_print("- Valid branches: " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", __nb_path_success);
    __debug_print("- ANT_COUNT(): " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", ANT_COUNT());
    __debug_print("- nb rooms: " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", __room_get_count());

    return (__links_start_count);
    // printf("Return: " COLOR_LIGHT_YELLOW "%d" COLOR_RESET "\n", __links_start_count > __links_end_count ? __links_start_count : __links_end_count);
    // return (__links_start_count > __links_end_count ? __links_start_count : __links_end_count);
}

static int __ek_free_all(EK_PATH *__ek_root)
{
    EK_PATH *tmp = __ek_root;
    while (tmp)
    {
        EK_NODE *node = tmp->root;
        while (node)
        {
            EK_NODE *tmp_node = node;
            node = node->next;
            free(tmp_node);
        }
        EK_PATH *tmp_path = tmp;
        tmp = tmp->next;
        free(tmp_path);
    }
    return (0);
}

static EK_PATH *__ek_merge_path(EK_PATH *__node_01, EK_PATH *__node_02)
{
    EK_PATH *__res = NULL;

    if (__node_01 == NULL)
        return (__node_02);
    else if (__node_02 == NULL)
        return (__node_01);

    if (__node_01->length <= __node_02->length)
    {
        __res = __node_01;
        __res->next = __ek_merge_path(__node_01->next, __node_02);
    }
    else
    {
        __res = __node_02;
        __res->next = __ek_merge_path(__node_01, __node_02->next);
    }
    return (__res);
}

void __ek_split_paths(EK_PATH *source, EK_PATH **front, EK_PATH **back)
{
    EK_PATH *ptr1;
    EK_PATH *ptr2;
    ptr2 = source;
    ptr1 = source->next;

    while (ptr1 != NULL)
    {
        ptr1 = ptr1->next;
        if (ptr1 != NULL)
        {
            ptr2 = ptr2->next;
            ptr1 = ptr1->next;
        }
    }
    *front = source;
    *back = ptr2->next;
    ptr2->next = NULL;
}

void __ek_merge_paths(EK_PATH **thead)
{
    EK_PATH *head = *thead;
    EK_PATH *ptr1;
    EK_PATH *ptr2;

    if ((head == NULL) || (head->next == NULL))
        return;
    __ek_split_paths(head, &ptr1, &ptr2);
    __ek_merge_paths(&ptr1);
    __ek_merge_paths(&ptr2);
    *thead = __ek_merge_path(ptr1, ptr2);
}

/*******************************************************************************
 *                                  EK PARSER                                  *
 ******************************************************************************/

int __best_link_depth = -1;
int __best_link_start_count = 0;
int __best_link_start_id = 0;

static int __ek_parser_mapping(EK_PATH *__ek_path, EK_NODE *__current_node, const t_room *current_room)
{
    __debug_print("Current Branch: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", __nb_path);
    __debug_print("Path Found: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", __nb_path_success);
    __debug_print_path(__ek_path);

    // Checkers - Stop branches
    const int __end_room_id = __room_get_end_room()->id;
    if (current_room->id == __end_room_id)
    {
        __debug_print(COLOR_LIGHT_YELLOW "  - End room reached: %d\n" COLOR_RESET, current_room->id);
        __nb_path_success++;
        if (__best_link_depth == -1)
            __best_link_depth = __ek_path->depth;

        // if (__ek_path->root->next && __best_link_start_id < __room_get_links_count(__room_get_start_room()->id))
        // {
        //     if (__ek_path->root->next->id == __room_get_start_room()->links[__best_link_start_id]->id)
        //     {
        //         __best_link_start_count++;
        //         __best_link_start_id++;
        //         __debug_print(COLOR_LIGHT_YELLOW "  - Start room reached: %d\n" COLOR_RESET, __room_get_start_room()->id);
        //     }
        // }

        return (1);
    }

    // TODO ! Opti cette parti (stop la recherche a un certain moment (map 6k))

    if (__ek_path->depth - BEST_LINK_OFFSET >= __best_link_depth && __best_link_depth >= 0)
    {
        __debug_print(COLOR_LIGHT_YELLOW "  - Stop branch: %d\n" COLOR_RESET, __ek_path->depth);
        __ek_delete_path(g_ek.paths, __ek_path);
        return (0);
    }

    __debug_print(COLOR_LIGHT_YELLOW "- %d > %d || %d > %d\n" COLOR_RESET, __current_node->depth, __room_get_count(),
                  __nb_path, __room_get_count());
    if (__current_node->depth >= __room_get_count())
    {
        __debug_print(COLOR_LIGHT_YELLOW "  - Depth reached: %d\n" COLOR_RESET, __current_node->depth);
        __ek_delete_path(g_ek.paths, __ek_path);
        return (0);
    }

    // if (__best_link_start_count >= __ek_max_branch())
    // {
    //     return (0);
    // }

    __debug_print(COLOR_LIGHT_YELLOW "- %d >= %d || %d >= %d\n" COLOR_RESET, __nb_path_success, __ek_max_branch(), __nb_path_success, ANT_COUNT());
    // if (__nb_path_success > __ek_max_branch() ||
    // __nb_path_success >= ANT_COUNT())
    // if (__nb_path_success >= ANT_COUNT())
    // {
    //     __debug_print(COLOR_LIGHT_YELLOW "  - Max branch reached: %d\n" COLOR_RESET, __nb_path_success);
    //     return (0);
    // }

    if (__ek_max_branch_stuck(__nb_path, __nb_path_success) == true)
    {
        __debug_print(COLOR_LIGHT_YELLOW "  - Max branch stuck: %d\n" COLOR_RESET, __nb_path_success);
        // __ek_delete_path(g_ek.paths, __ek_path);
        return (0);
    }

    const int __links_count = __room_get_links_count(current_room->id);

    t_room *__valid_links[__links_count + 1];
    const int __valid_links_count = __ek_get_valid_links(__ek_path, __valid_links, __links_count, current_room->links);
    __debug_print("Current room: %d has %d links\n", current_room->id, __valid_links_count);
    if (__valid_links_count == 1)
    {
        const t_room *__room_link = __valid_links[0];
        EK_NODE *new_node = __ek_create_node(__current_node, __room_link->id);
        __ek_push_node(__ek_path, new_node);
        __ek_parser_mapping(__ek_path, new_node, __room_link);
    }
    else if (__valid_links_count > 1)
    {
        for (int i = 0; i < __valid_links_count; i++)
        {
            const t_room *__room_link = __valid_links[i];
            EK_PATH *new_path = __ek_create_path(__ek_path);
            __ek_copy_path(new_path, __ek_path, __current_node);

            __ek_path = __ek_push_path(__ek_path, new_path);

            __debug_print(COLOR_LIGHT_BLUE "Test: \n" COLOR_RESET);
            __debug_print_path(__ek_path);
            __debug_wait_input();

            EK_NODE *new_node = __ek_create_node(__current_node, __room_link->id);
            __ek_push_node(new_path, new_node);

            __debug_wait_input();
            int ret = __ek_parser_mapping(new_path, new_node, __room_link);
            if (ret == 1)
            {
                return (0);
            }
        }
    }
    else
    {
        __ek_delete_path(g_ek.paths, __ek_path);
    }
    return (0);
}

static int __ek_parser(void)
{
    __debug_print(COLOR_LIGHT_CYAN "--- EK PARSER ---\n" COLOR_RESET);
    EK_PATH *current_path = NULL;
    EK_NODE *current_node = NULL;

    const t_room *__start_room = __room_get_start_room();

    current_path = __ek_create_path(NULL);
    g_ek.paths = __ek_push_path(g_ek.paths, current_path);
    current_node = __ek_create_node(NULL, __start_room->id);
    __ek_push_node(current_path, current_node);

    __debug_print_all_paths(g_ek.paths);
    __ek_parser_mapping(current_path, current_node, __start_room);

    // Prune manualy all paths that are not valid
    EK_PATH *path = g_ek.paths;
    EK_PATH *next_path = NULL;
    const t_room *__end_room = __room_get_end_room();
    while (path)
    {
        EK_NODE *node = path->root;
        while (node->next)
            node = node->next;
        if (node->id != __end_room->id)
        {
            __debug_print(COLOR_LIGHT_RED "  - Prune path: " COLOR_RESET);
            __debug_print_path(path);
            next_path = path->next;
            __ek_delete_path(g_ek.paths, path);
            if (g_ek.paths == path)
            {
                EK_PATH *tmp = g_ek.paths;
                g_ek.paths = g_ek.paths->next;
                free(tmp);
            }
        }
        else
            next_path = path->next;
        path = next_path;
    }
    __debug_print_all_paths(g_ek.paths);
    __debug_print("\n\n");

    EK_PATH *tmp = g_ek.paths;
    __ek_merge_paths(&(tmp));
    __debug_print_all_paths(g_ek.paths);
    // pause();

    // printf(COLOR_LIGHT_GREEN "### EK PARSER END ###\n" COLOR_RESET);
    // exit(1);
    return (0);
}

/*******************************************************************************
 *                                  EK SOLVER                                  *
 ******************************************************************************/

static int __ek_get_valid_next_nodes(EK_PATH *__ref_root, EK_NODE *__valid_next_nodes[], int __current_links, int __current_room_id)
{
    if (__ref_root == NULL)
        return (0);
    if (__ref_root->root == NULL)
        return (0);
    ft_bzero(__valid_next_nodes, sizeof(EK_NODE *) * __current_links + 1);

    EK_PATH *__path = __ref_root;
    int best_path_length = __path->length;
    int i = 0;
    while (__path)
    {
        __debug_print("New Path: ");
        __debug_print_path(__path);
        EK_NODE *node = __path->root;
        if (node == NULL)
        {
            __path = __path->next;
            continue;
        }
        // if (__path->length - node->depth > best_path_length)
        // {
        //     best_path_length = __path->length;
        //     __path = __path->next;
        //     continue;
        // }
        while (node->next)
        {
            // __path->length - node->next->depth < best_path_length &&
            //
            // node->id == __current_room_id && __room_get_room(node->next->id)->type == END
            if (node->id == __current_room_id &&
                __ek_ant_is_in_node(g_ants, node->next) == false)
            {
                __debug_print("Add valid node: %d\n", node->next->id);
                __valid_next_nodes[i] = node->next;
                best_path_length = __path->length - node->next->depth;
                i++;
            }
            node = node->next;
        }
        __path = __path->next;
    }
    __valid_next_nodes[i] = NULL;
    return (i);
}

static int __ek_solver(ANT *ant)
{
    // Find next room
    const t_room *__current_ant_room = ant->current_room;

    // Find best next room
    const int __links_count = __room_get_links_count(__current_ant_room->id);
    EK_NODE **__valid_next_nodes;

    if (!(__valid_next_nodes = malloc(sizeof(EK_NODE) * (__links_count + 1) * (__nb_path + 1))))
        return (1);
    const int __valid_links_count = __ek_get_valid_next_nodes(g_ek.paths, __valid_next_nodes, __links_count, __current_ant_room->id);

    __debug_print("Valid links count: %d\n", __valid_links_count);
    EK_NODE *__best_node = NULL;

    for (int i = 0; i < __valid_links_count && __valid_next_nodes[i] != NULL; i++)
    {
        __debug_print("Valid node id: %d\n", __valid_next_nodes[i]->id);
        const t_room *__next_room = __room_get_room(__valid_next_nodes[i]->id);
        EK_NODE *__current_node = __valid_next_nodes[i];
        __debug_print("Next room: %s\n", __next_room->name);
        if (__best_node == NULL)
        {
            __best_node = __valid_next_nodes[i];
            continue;
        }
        else
        {
            if (__next_room->type == END)
            {
                __best_node = __valid_next_nodes[i];
                break;
            }
            else if (__current_node->value > __best_node->value)
            {
                __best_node = __current_node;
                continue;
            }
        }
    }

    if (__best_node)
    {
        __debug_print("Best node id: %d\n", __best_node->id);
        ant->current_room = __room_get_room(__best_node->id);
        printf("L%d-%s ", ant->id + 1, ant->current_room->name);
        ant->moved = true;
    }
    free(__valid_next_nodes);
    __valid_next_nodes = NULL;
    __debug_wait_input();
    return (0);
}

/*******************************************************************************
 *                                   AI MAIN                                   *
 ******************************************************************************/

int ai_main(void)
{
    // printf(COLOR_LIGHT_GREEN "### AI MAIN ###\n\n" COLOR_RESET);

    if ((__ants_init()) == 1)
        return (1);
    if ((__ek_init_ek()) == 1)
        return (1);
    if ((__ek_parser()) == 1)
        return (1);

    // Separation between map and resolution
    printf("\n");
    // turn zero
    add_turn(g_ants);

    __debug_print(COLOR_LIGHT_CYAN "-- ALL PATHS --\n" COLOR_RESET);
    __debug_print_all_paths(g_ek.paths);

    // pause();

    size_t turn = 0;
    while (__utils_check_end() == false)
    {
        __debug_print(COLOR_LIGHT_RED "\n### TURN [%d] ###\n\n" COLOR_RESET, turn);

        bool __force_exit = false;
        for (int j = 0; j <= 1; j++)
        {
            for (int i = 0; i < ANT_COUNT(); i++)
            {
                __debug_print(COLOR_LIGHT_RED "----- Ant " COLOR_LIGHT_CYAN "[%d]" COLOR_RESET COLOR_LIGHT_RED " -----\n" COLOR_RESET, g_ants[i].id);
                if (g_ants[i].moved == false && g_ants[i].current_room->type != END)
                {
                    if ((__ek_solver(&g_ants[i])) == 1)
                        return (1);
                    if (g_ants[i].moved == false && g_ants[i].current_room->type == START)
                    {
                        __force_exit = true;
                        break;
                    }
                }
                if (__force_exit == true)
                {
                    __force_exit = false;
                    break;
                }
            }
        }
        for (int i = 0; i < ANT_COUNT(); i++)
            g_ants[i].moved = false;
        ++turn;
        printf("\n");
        add_turn(g_ants);
    }
    if (AI_VERBOSE == true)
        printf(COLOR_LIGHT_GREEN "### PATH SOLVED IN [%ld] turns ###\n" COLOR_RESET, turn);
    __debug_print_all_paths(g_ek.paths);
    __ants_free();
    __ek_free_all(g_ek.paths);
    return (0);
}