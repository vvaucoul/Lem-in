/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:02:24 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 13:11:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/classes/vector.h"

/*******************************************************************************
 *                             MEMBERS - FUNCTIONS                             *
 ******************************************************************************/

static void *realloc_root(Vector *vector, size_t new_size)
{
    void **new_root;

    if (!(new_root = malloc(sizeof(void *) * (new_size + 1))))
        return (NULL);
    new_root[0] = NULL;
    for (size_t i = 0; i < new_size; i++)
    {
        new_root[i] = vector_at(vector, i);
        new_root[i + 1] = NULL;
    }
    free(vector->root);
    vector->root = new_root;
    return (vector->root);
}

static size_t vector_find(Vector *vector, void *ptr)
{
    size_t i;

    i = 0;
    while (i < vector->size)
    {
        if ((vector->root)[i] == ptr)
            return (i);
        i++;
    }
    return (i);
}

Vector *vector_new(size_t size, size_t count)
{
    Vector *vector;

    vector = (Vector *)ft_calloc(sizeof(Vector), 1);
    if (vector == NULL)
        return (NULL);
    if (!(vector->root = ft_calloc(size, count)))
    {
        free(vector);
        return (NULL);
    }
    vector->root[0] = NULL;
    vector->size = 0;
    return (vector);
}

void vector_delete(Vector *vector)
{
    if (vector == NULL)
        return;
    free(vector->root);
    free(vector);
}

/*******************************************************************************
 *                                  CAPACITY                                   *
 ******************************************************************************/

size_t vector_size(Vector *vector)
{
    return (vector->size);
}

size_t vector_max_size(Vector *vector)
{
    return (INT_MAX / sizeof(vector->root));
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector_size(vector))
        realloc_root(vector, size);
    else if (size < vector_size(vector))
    {
        vector->size = size;
        realloc_root(vector, size);
    }
}

size_t vector_capacity(Vector *vector)
{
    return (vector_max_size(vector) - vector_size(vector));
}

int vector_empty(Vector *vector)
{
    return (vector_size(vector) == 0);
}

void vector_reserve(Vector *vector, size_t size)
{
    vector_resize(vector, vector_size(vector) + size);
}

/*******************************************************************************
 *                              ELEMENT - ACCESS                               *
 ******************************************************************************/

void *vector_at(Vector *vector, size_t index)
{
    if (index >= vector_size(vector))
        return (NULL);
    return (vector->root[index]);
}

void *vector_front(Vector *vector)
{
    return (vector->root[0]);
}

void *vector_back(Vector *vector)
{
    return (vector->root[vector_size(vector) - 1]);
}

void *vector_data(Vector *vector)
{
    return (*vector->root);
}

/*******************************************************************************
 *                                  MODIFIERS                                  *
 ******************************************************************************/

void vector_assign(Vector *vector, void **ptrs)
{
    size_t i;
    size_t ptrs_len = 0;

    i = 0;
    if (!ptrs || !ptrs[0])
        return;
    else
    {
        while (ptrs[i] != NULL)
        {
            ptrs_len++;
            ++i;
        }
    }
    i = 0;
    vector_resize(vector, ptrs_len);
    while (i < vector_size(vector))
    {
        (vector->root)[i] = ((ptrs)[i]);
        i++;
    }
}

void vector_push_back(Vector *vector, void *ptr)
{
    vector_resize(vector, vector_size(vector) + 1);
    (vector->root)[vector_size(vector)] = ptr;
    ++vector->size;
}

void vector_pop_back(Vector *vector)
{
    vector_resize(vector, vector_size(vector) - 1);
}

void vector_insert(Vector *vector, void *ptr, size_t index)
{
    size_t i;

    if (index > vector_size(vector))
        return;
    vector_resize(vector, vector_size(vector) + 1);
    i = vector_size(vector) - 1;
    while (i > index)
    {
        (vector->root)[i] = (vector->root)[i - 1];
        i--;
    }
    (vector->root)[index] = ptr;
}

void vector_erase(Vector *vector, size_t index)
{
    size_t i;

    if (index >= vector_size(vector))
        return;
    i = index;
    while (i < vector_size(vector) - 1)
    {
        (vector->root)[i] = (vector->root)[i + 1];
        i++;
    }
    vector_resize(vector, vector_size(vector) - 1);
}

void vector_swap(Vector *vector, size_t index, size_t index2)
{
    void *tmp;

    if (index >= vector_size(vector) || index2 >= vector_size(vector))
        return;
    tmp = (vector->root)[index];
    (vector->root)[index] = (vector->root)[index2];
    (vector->root)[index2] = tmp;
}

void vector_swap_ptrs(Vector *vector, void *ptr, void *ptr2)
{
    size_t index;
    size_t index2;

    index = vector_find(vector, ptr);
    index2 = vector_find(vector, ptr2);
    vector_swap(vector, index, index2);
}

void vector_clear(Vector *vector)
{
    vector_resize(vector, 0);
}
