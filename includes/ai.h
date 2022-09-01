/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:29:34 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/20 20:40:00 by vvaucoul         ###   ########.fr       */
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

#define AI_VERBOSE 0
#define AI_DEBUG_INPUT 0

typedef struct s_ek_node
{
    struct s_ek_node *next;   // Next Nodes (links)
    struct s_ek_node *parent; // Parent Node
    int depth;                // Depth
    int value;                // Value [Sum of weights | Start + End]
    int id;                   // Node ID -> Ref to Room ID
} __attribute__((packed)) t_ek_node;

typedef struct s_ek_path
{
    t_ek_node *root;        // Root Node
    int depth;              // Depth
    int length;             // Length
    struct s_ek_path *next; // Next Path
    struct s_ek_path *prev; // Previous Path
} __attribute__((packed)) t_ek_path;

typedef struct s_ek
{
    t_ek_path *paths; // Paths | Linked list
} __attribute__((packed)) t_ek;

#define EK_NODE t_ek_node
#define EK_PATH t_ek_path
#define EK t_ek

/* ANTS */

typedef struct s_ant
{
    int id;
    int x;
    int y;
    bool moved;
    t_room *current_room;
} __attribute__((packed, aligned(4))) t_ant;

/*******************************************************************************
 *                              LEM-IN AI DEFINES                              *
 ******************************************************************************/

/* EK */

#define GET_EK_PATH(x) (g_ek[x])
#define PATH_COUNT() (g_ek.path_count)

#define MAX_BRANCH_STUCK 300 // Max branch stuck
#define BEST_LINK_OFFSET 10 // Best link offset

/* ROOMS */

#define ROOM_TYPE_TO_STRING(x) (x == START ? "START" : (x == END ? "END" : "NORMAL"))

/* ANTS */

#define ANT t_ant
#define ANT_COUNT() ((int)g_gameinfo.ant_count)
#define GET_ANT(x) (g_ants[x])

extern ANT *g_ants;
extern EK g_ek;
extern int __nb_path;
extern int __nb_path_success;
extern int ai_main(void);

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

#endif /* AI_H */