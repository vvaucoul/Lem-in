/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai-global.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:07:56 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:24:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_GLOBAL_H
#define AI_GLOBAL_H

/*******************************************************************************
 *                                EK STRUCTURES                                *
 ******************************************************************************/

typedef struct s_ek_room
{
    int room_ref;
    int depth;
    struct s_ek_room *next;
} t_ek_room;

typedef struct s_ek_path
{
    t_ek_room *room;
    int depth;
    struct s_ek_path *next;
    int id;
} t_ek_path;

typedef struct s_ek_graph
{
    t_ek_path *root_path;
} t_ek_graph;

#define EkRoom t_ek_room
#define EkPath t_ek_path
#define EkGraph t_ek_graph

/*******************************************************************************
 *                               LILO / VISITED                                *
 ******************************************************************************/

#define LILO_STACK_IS_EMPTY() (g_lilo_stack && g_lilo_stack[0] == -1)

/*******************************************************************************
 *                                  AI - MAP                                   *
 ******************************************************************************/

typedef struct s_ai_room
{
    int room_ref;
    int weight;
    struct s_ai_room **links;
} t_ai_room;

#define AiRoom t_ai_room
#define AI_ROOM_IS_EMPTY(x) (x == NULL || x->room_ref == -1)

#endif