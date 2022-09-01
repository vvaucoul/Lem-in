/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:33:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/16 13:48:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_H
#define AI_H

#include "lem_in.h"

/*******************************************************************************
 *                                   COLORS                                    *
 ******************************************************************************/

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

#define COLOR_LIGHT_RED "\x1b[91m"
#define COLOR_LIGHT_GREEN "\x1b[92m"
#define COLOR_LIGHT_YELLOW "\x1b[93m"
#define COLOR_LIGHT_BLUE "\x1b[94m"
#define COLOR_LIGHT_MAGENTA "\x1b[95m"
#define COLOR_LIGHT_CYAN "\x1b[96m"

#define COLOR_RESET "\x1b[0m"

typedef struct s_ek_node
{
    struct s_ek_node *next; // Next Node
    struct s_ek_node *prev; // Previous Node
    int depth;              // Depth
    int id;                 // Node ID -> Ref to Room ID
    bool flag;              // Flag -> Used to know if the node is visited or not
} __attribute__((packed)) t_ek_node;

typedef struct s_ek_path
{
    t_ek_node *root;        // Root Node
    t_ek_node *current;     // Current Node
    int depth;              // Depth
    struct s_ek_path *next; // Next Path
} __attribute__((packed)) t_ek_path;

typedef struct s_ek
{
    t_ek_path *paths;        // Paths | Linked list | Start Paths
    t_ek_path *current_path; // Path chosen last turn | To save it next turn
    t_ek_path *best_path;    // Best Path | To save it next turn
} __attribute__((packed)) t_ek;

#define EK_NODE t_ek_node
#define EK_PATH t_ek_path
#define EK t_ek

extern EK *g_ek;

/* ANTS */

typedef struct s_ant
{
    int id;
    int x;
    int y;
    t_room *current_room;
} __attribute__((packed, aligned(4))) t_ant;

extern int ai_main(void);

/*******************************************************************************
 *                              LEM-IN AI DEFINES                              *
 ******************************************************************************/

/* EK */

#define GET_EK_PATH(x) (g_ek[x])
#define PATH_COUNT() (g_ek.path_count)

/* ROOMS */

#define ROOM_TYPE_TO_STRING(x) (x == START ? "START" : (x == END ? "END" : "NORMAL"))

/* ANTS */

#define ANT t_ant
#define ANT_COUNT() ((int)g_gameinfo.ant_count)
#define GET_ANT(x) (g_ants[x])

/*******************************************************************************
 *                          LEM-IN AI UTILS FUNCTIONS                          *
 ******************************************************************************/

/* INTEGERS */

static inline int __room_get_count(void)
{
    return (get_room_count());
}

static inline int __room_get_id(const char *name)
{
    if (!name)
        return (-1);
    return (get_room_id((char *)name));
}

static inline int __room_get_links_count(int room_id)
{
    if (room_id < 0 || room_id >= __room_get_count())
        return (-1);
    return (get_room_links_count(room_id));
}

static inline int __room_get_link_id(int room_id, int link_id)
{
    if (room_id < 0 || room_id >= __room_get_count())
        return (-1);
    else if (link_id < 0 || link_id >= __room_get_count())
        return (-1);
    return (get_link_id(room_id, link_id));
}

/* ROOMS */

static inline t_room *__room_get_room(int room_id)
{
    if (room_id < 0 || room_id >= __room_get_count())
        return (NULL);
    return (get_room(room_id));
}

static inline t_room *__room_get_start_room(void)
{
    return (get_start_room());
}

static inline t_room *__room_get_end_room(void)
{
    return (get_end_room());
}

/* AI UTILS */

static inline bool __ai_is_end_room(const t_room *r1, const t_room *r2)
{
    if (!r1 || !r2)
        return (false);
    else if (r1->type == END && r2->type == END && r1->id == r2->id)
        return (true);
    else
        return (false);
}

static inline bool __ai_room_as_been_visited(EK_PATH *__ek_path, const t_room *room)
{
    if (!__ek_path || !room)
        return (false);
    EK_NODE *node = __ek_path->root;
    while (node)
    {
        if (node->id == room->id)
            return (true);
        node = node->next;
    }
    return (false);
}

static inline EK_NODE *__ai_get_last_node(EK_PATH *__ek_path)
{
    if (!__ek_path)
        return (NULL);
    EK_NODE *node = __ek_path->root;
    if (!node)
        return (NULL);
    while (node->next)
        node = node->next;
    return (node);
}

static inline EK_NODE *__ai_get_node_by_id(EK_PATH *__ek_path, int id)
{
    if (!__ek_path)
        return (NULL);
    EK_NODE *node = __ek_path->root;
    while (node)
    {
        const t_room *room = __room_get_room(node->id);
        if (room->id == id)
            return (node);
        node = node->next;
    }
    return (NULL);
}

static inline bool __ai_any_ant_is_in_room(const ANT *ants, const EK_NODE *node)
{
    if (!node)
        return (false);
    for (int i = 0; i < ANT_COUNT(); i++)
    {
        const ANT *ant = &(ants[i]);
        if (ant->current_room->id == node->id)
            return (true);
    }
    return (false);
}

static inline bool __ai_node_next_node_is_valid(const ANT *ants, EK_NODE *node)
{
    if (node == NULL)
        return (false);
    else if (node->next)
    {
        // if (node->next->flag == false)
        // {
            const bool __ant_in_room = __ai_any_ant_is_in_room(ants, node->next);
            printf("%s: %d\n", __func__, __ant_in_room);
            if (__ant_in_room == true)
                return (false);
            else
                return (true);
        // }
    }
    return (false);
}

#endif /* AI_H */