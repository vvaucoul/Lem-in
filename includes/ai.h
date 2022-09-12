/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:59:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:31:18 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_H
#define AI_H

#pragma once

#include "lem_in.h"
#include "ai-utils.h"
#include "ai-ek.h"
#include "ai-global.h"
#include "ai-ggc.h"

/*******************************************************************************
 *                                EK STRUCTURES                                *
 ******************************************************************************/

extern EkGraph *g_ek_graph;

/*******************************************************************************
 *                               LILO / VISITED                                *
 ******************************************************************************/

extern int *g_lilo_stack;
extern int *g_visited_rooms;

extern int __lilo_init(void);
extern void __lilo_free(void);
extern int __lilo_add_room(int room_id);
extern int __lilo_remove_room(int room_id);
extern int __lilo_add_visited_room(int room_id);
extern bool __lilo_room_as_been_visited(int room_id);
extern int *__lilo_get_instance(void);
extern void __lilo_free_instance(int *instance_lilo_stack);

/*******************************************************************************
 *                                  AI - MAP                                   *
 ******************************************************************************/

extern AiRoom **g_ai_rooms;

extern int __ai_room_init(void);
extern AiRoom *__ai_room_create_room(int room_ref, int weight);
extern void __ai_room_push_room(AiRoom *room);
extern AiRoom *__ai_room_get_room_by_id(int id);
extern int __ai_rooms_update_links();
extern int __ai_room_get_links_count(AiRoom *ref);
extern void __ai_rooms_free(void);
extern AiRoom *__ai_room_get_start_room(void);
extern AiRoom *__ai_room_get_end_room(void);
extern AiRoom *__ai_room_get_ant_room(ANT *ant);
extern int __ai_rooms_fix_links();

/*******************************************************************************
 *                                   SOLVER                                    *
 ******************************************************************************/

extern int __ek_solver(ANT *ant);

/*******************************************************************************
 *                              GLOBAL STRUCTURE                               *
 ******************************************************************************/

#endif /* !AI_H */
