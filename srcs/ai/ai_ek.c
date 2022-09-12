/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_ek.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:34:46 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:31:54 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>

int __path_id = 0;

/*******************************************************************************
 *                              EK / EDMOND KARP                               *
 ******************************************************************************/

void __ek_free_room(EkRoom *room)
{
    if (!(room))
        return;
    else
    {
        free(room);
        room = NULL;
    }
}

void __ek_free_path(EkPath *path)
{
    if (!(path))
        return;
    else
    {
        EkRoom *tmp = path->room;
        EkRoom *prev = NULL;

        while (tmp)
        {
            prev = tmp;
            tmp = tmp->next;
            if (prev)
                __ek_free_room(prev);
        }
    }
}

void __ek_free(EkGraph *graph)
{
    EkPath *path = graph->root_path;

    if (!path)
        return;
    else
    {
        EkPath *prev_path = NULL;
        while (path)
        {
            prev_path = path;
            __ek_free_path(prev_path);
            prev_path = NULL;
            path = path->next;
        }
    }
    __free_gcc_ek();
    free(g_ek_graph);
}

EkRoom *__ek_create_room(int room_ref, int depth)
{
    EkRoom *room = NULL;

    if (!(room = malloc(sizeof(EkRoom))))
        exit(__return_error("__ek_create_room malloc failed", 1));
    else
    {
        room->room_ref = room_ref;
        room->depth = depth;
        room->next = NULL;
    }
    return (room);
}

EkPath *__ek_create_path(EkRoom *first_room)
{
    EkPath *path = NULL;

    if (!(path = malloc(sizeof(EkPath))))
        exit(__return_error("__ek_create_path malloc failed", 1));
    else
    {
        path->room = first_room;
        path->depth = 0;
        path->id = __path_id;
        path->next = NULL;
        __add_gcc_ek(path);
    }
    return (path);
}

EkGraph *__ek_create_graph(void)
{
    EkGraph *graph = NULL;

    if (!(graph = malloc(sizeof(EkGraph))))
        exit(__return_error("__ek_create_graph malloc failed", 1));
    else
    {
        graph->root_path = NULL;
    }
    return (graph);
}

int __ek_graph_push_room(EkPath *current_path, EkRoom *room_ref)
{
    if (current_path == NULL || room_ref == NULL)
        return (__return_error("EkPath or EkRoom is empty", 1));
    else
    {
        EkRoom *tmp = current_path->room;

        if (!tmp)
        {
            current_path->room = room_ref;
            return (0);
        }
        else
        {
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = room_ref;
        }
    }
    return (0);
}

EkRoom *__ek_get_last_room(EkPath *path)
{
    EkRoom *tmp = path->room;

    if (!tmp)
        return (NULL);
    else
    {
        while (tmp->next)
            tmp = tmp->next;
    }
    return (tmp);
}

int __ek_graph_push_path(EkGraph *graph, EkPath *new_path)
{
    if (graph == NULL || new_path == NULL)
        return (__return_error("EkPath is empty", 1));
    else
    {
        EkPath *tmp = graph->root_path;

        if (!tmp)
            graph->root_path = new_path;
        else
        {
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = new_path;
        }
    }
    return (0);
}

EkPath *__ek_append_path(EkPath *ref, EkPath *to_append)
{
    EkPath *__new_path = NULL;

    if (!ref || !to_append)
        return (NULL);
    else if (!ref->room || !to_append->room)
        return (NULL);
    if (!(__new_path = malloc(sizeof(EkPath))))
        exit(__return_error("__ek_append_path malloc failed", 1));
    else
    {
        __new_path->room = NULL;
        __new_path->depth = 0;
        __new_path->id = __path_id;
        __new_path->next = NULL;

        EkRoom *tmp = ref->room;

        while (tmp)
        {
            EkRoom *__copy = __ek_create_room(tmp->room_ref, tmp->depth);
            __ek_graph_push_room(__new_path, __copy);
            tmp = tmp->next;
        }
        tmp = to_append->room;
        while (tmp)
        {
            EkRoom *__copy = __ek_create_room(tmp->room_ref, tmp->depth);
            __ek_graph_push_room(__new_path, __copy);
            EkRoom *prev = tmp;
            tmp = tmp->next;
            free(prev);
        }
    }
    __add_gcc_ek(__new_path);
    ++__path_id;
    return (__new_path);
}

EkPath *__ek_graph_prune_path(EkGraph *graph, EkPath *path, EkPath *prev)
{
    EkPath *tmp = NULL;

    if (prev == NULL)
    {
        tmp = graph->root_path;
        __ek_free_path(tmp);
        graph->root_path = graph->root_path->next;
        return (graph->root_path);
    }
    else
    {
        tmp = prev->next;
        __ek_free_path(tmp);
        prev->next = path->next;
        return (prev->next);
    }
}

void __ek_graph_prune_paths(EkGraph *graph)
{
    EkPath *tmp = graph->root_path;
    const int room_ref_id = __room_get_end_room()->id;

    if (!tmp)
        return;
    else
    {
        EkPath *prev = NULL;
        while (tmp)
        {
            const EkRoom *__last_room = __ek_get_last_room(tmp);
            if (__last_room->room_ref != room_ref_id)
            {
                tmp = __ek_graph_prune_path(graph, tmp, prev);
                continue;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
}
