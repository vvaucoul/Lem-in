/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto-allocator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:45:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 11:01:35 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/auto-allocator.h"

AAL _g_auto_allocator = {NULL, 0};

static void *add_ptr_to_list(void *ptr)
{
    t_node *new_elem;

    if ((new_elem = malloc(sizeof(t_node))) == NULL)
        return (NULL);
    new_elem->data = ptr;
    new_elem->next = NULL;

    if (!_g_auto_allocator.nodes)
        _g_auto_allocator.nodes = new_elem;
    else
    {
        t_node *tmp = _g_auto_allocator.nodes;

        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_elem;
    }
    ++_g_auto_allocator.node_size;
    return (ptr);
}
static void remove_ptr_from_list(void *ptr)
{
    t_node *tmp = _g_auto_allocator.nodes;
    t_node *prev = NULL;

    if (tmp && tmp->data == ptr)
    {
        _g_auto_allocator.nodes = tmp->next;
        free(tmp->data);
        free(tmp);
        --_g_auto_allocator.node_size;
        return;
    }

    while (tmp && tmp->data != ptr)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp->data);
    free(tmp);
    --_g_auto_allocator.node_size;
}

void *AA_allocate_ptr(size_t size, size_t count)
{
    if (size == 0 || count == 0)
        return (NULL);
    else
    {
        void *ptr = ft_calloc(size, count);

        if (ptr)
        {
            if (!(add_ptr_to_list(ptr)))
                return (NULL);
            return (ptr);
        }
        else
            return (NULL);
    }
    return (NULL);
}
void AA_free_ptr(void *ptr)
{
    if (ptr)
    {
        t_node *tmp = _g_auto_allocator.nodes;

        while (tmp && tmp->data != ptr)
            tmp = tmp->next;
        if (tmp != NULL)
            remove_ptr_from_list(ptr);
    }
}
void AA_free(void)
{
    t_node *current = _g_auto_allocator.nodes;
    t_node *tmp = NULL;

    WHILE_AA_PTR(current)
    {
        tmp = current;
        current = current->next;
        free(tmp->data);
        free(tmp);
        --_g_auto_allocator.node_size;
    }
    _g_auto_allocator.nodes = NULL;
}

void AA_push_ptr(void *ptr)
{
    if (ptr)
    {
        t_node *tmp = _g_auto_allocator.nodes;

        while (tmp && tmp->data != ptr)
            tmp = tmp->next;
        if (tmp == NULL)
        {
            if (!(add_ptr_to_list(ptr)))
                return;
        }
    }
}

size_t AA_get_node_size(void)
{
    return (_g_auto_allocator.node_size);
}
void AA_print_nodes(void)
{
    size_t i = 0;

    if (_g_auto_allocator.nodes != NULL)
    {
        FOR_EACH_AA_PTR()
        {
            printf("Node [%zu] = %p | Next -> %p\n", i, current, current->next);
            ++i;
        }
    }
    if (i == 0)
        printf("No nodes\n");
}