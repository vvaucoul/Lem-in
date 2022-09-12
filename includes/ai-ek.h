/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai-ek.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:35:11 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/08 16:02:48 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_EK
#define AI_EK

#include <ai-global.h>

extern void __ek_free(EkGraph *graph);
extern void __ek_free_room(EkRoom *room);
extern void __ek_free_path(EkPath *path);
extern EkRoom *__ek_create_room(int room_ref, int depth);
extern EkPath *__ek_create_path(EkRoom *first_room);
extern EkGraph *__ek_create_graph(void);
extern int __ek_graph_push_room(EkPath *current_path, EkRoom *room_ref);
extern EkRoom *__ek_get_last_room(EkPath *path);
extern int __ek_graph_push_path(EkGraph *graph, EkPath *new_path);
extern EkPath *__ek_append_path(EkPath *ref, EkPath *to_append);
extern EkPath *__ek_graph_prune_path(EkGraph *graph, EkPath *path, EkPath *prev);
extern void __ek_graph_prune_paths(EkGraph *graph);

extern int __path_id;

#endif