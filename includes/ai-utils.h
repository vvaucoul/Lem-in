/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai-utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:01:27 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 13:02:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_UTILS_H
#define AI_UTILS_H

#include <stdlib.h>
#include "lem_in.h"
#include "ai-global.h"

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
#define COLOR_LIGHT_WHITE "\x1b[97m"

#define COLOR_RESET "\x1b[0m"

/*******************************************************************************
 *                                 STRUCTURES                                  *
 ******************************************************************************/

/* ANTS */

typedef struct s_ant
{
    int id;
    int x;
    int y;
    bool moved;
    t_room *current_room;
} t_ant;

#define ANT t_ant
#define ANT_COUNT() ((int)g_gameinfo.ant_count)
#define GET_ANT(x) (g_ants[x])

extern ANT *g_ants;
extern int ai_main(void);

#define AI_VERBOSE 0
#define AI_DEBUG_INPUT 0

/*******************************************************************************
 *                           LEM-IN UTILS FUNCTIONS                            *
 ******************************************************************************/

extern void __debug_print(char *str, ...);
extern void __debug_wait_input(void);
extern void __debug_print_path(EkPath *path);
extern void __debug_display_lilo(int *__lilo);
extern void __debug_display_visited(int *__visited);
extern void __debug_display_ai_rooms(AiRoom **rooms);
extern void __debug_print_graph(EkGraph *graph);

extern bool __utils_check_end(void);
extern int __return_error(const char *str, int error);

extern int __ants_init(void);
extern int __ants_free(void);

/*******************************************************************************
 *                                LEM-IN MACROS                                *
 ******************************************************************************/

#define CONST_ROOM(x) ((const t_room *)(x))
#define ROOM(x) ((t_room *)(x))

#define ROOM_NAME(x) (__room_get_room(x)->name)

#define RECURSIVE_MAX_DEPTH 0x61A8 /* 25000 */

/*******************************************************************************
 *             LEM-IN UTILS FUNCTIONS - REF PARSING - INLINE MODE              *
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

#endif /* !AI_UTILS_H */