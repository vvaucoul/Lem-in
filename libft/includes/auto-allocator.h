/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto-allocator.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:44:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 11:17:18 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_ALLOCATOR_H
#define AUTO_ALLOCATOR_H

#include "libft.h"
#include <stdlib.h>

typedef struct s_node
{
    void *data;
    struct s_node *next;
} t_node;

typedef struct s_auto_allocator
{
    t_node *nodes;
    size_t node_size;
} t_auto_allocator;

#define AAL t_auto_allocator

extern AAL _g_auto_allocator;

#define FOR_EACH_AA_PTR() for (t_node *current = _g_auto_allocator.nodes; current; current = current->next)
#define WHILE_AA_PTR(ptr) while (ptr != NULL)

/*******************************************************************************
 *                         AUTO-ALLOCATOR - FUNCTIONS                          *
 ******************************************************************************/

void *AA_allocate_ptr(size_t size, size_t var_size);
void AA_free_ptr(void *ptr);
void AA_push_ptr(void *ptr);
void AA_free(void);
size_t AA_get_node_size(void);
void AA_print_nodes(void);

/*******************************************************************************
 *                     AUTO-ALLOCATOR - UTILS - FUNCTIONS                      *
 ******************************************************************************/


#endif