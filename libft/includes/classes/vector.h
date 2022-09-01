/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:02:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/04 17:26:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <limits.h>
#include "../libft.h"

typedef struct s_vector
{
    void **root;
    size_t size;
} t_vector;

#define Vector t_vector

Vector *vector_new(size_t size, size_t count);
void vector_delete(Vector *vector);

/*******************************************************************************
 *                                  CAPACITY                                   *
 ******************************************************************************/

size_t vector_size(Vector *vector);
size_t vector_max_size(Vector *vector);
void vector_resize(Vector *vector, size_t size);
size_t vector_capacity(Vector *vector);
int vector_empty(Vector *vector);
void vector_reserve(Vector *vector, size_t size);

/*******************************************************************************
 *                              ELEMENT - ACCESS                               *
 ******************************************************************************/

void *vector_at(Vector *vector, size_t index);
void *vector_front(Vector *vector);
void *vector_back(Vector *vector);
void *vector_data(Vector *vector);

/*******************************************************************************
 *                                  MODIFIERS                                  *
 ******************************************************************************/

void vector_assign(Vector *vector, void **ptrs);
void vector_push_back(Vector *vector, void *ptr);
void vector_pop_back(Vector *vector);
void vector_insert(Vector *vector, void *ptr, size_t index);
void vector_erase(Vector *vector, size_t index);
void vector_swap(Vector *vector, size_t index, size_t index2);
void vector_swap_ptrs(Vector *vector, void *ptr, void *ptr2);
void vector_clear(Vector *vector);

#endif