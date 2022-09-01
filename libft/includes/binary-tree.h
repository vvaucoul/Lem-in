/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary-tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:15:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 11:42:14 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_t_node
{
    void *data;
    struct s_t_node *left;
    struct s_t_node *right;
} t_t_node;

#define T_NODE t_t_node

typedef struct s_bt
{
    T_NODE *root;
    size_t node_size;
} t_bt;

#define T_BT t_bt

extern T_BT _g_bt;

/*******************************************************************************
 *                           BINARY_TREE - FUNCTIONS                           *
 ******************************************************************************/

T_NODE *BT_new_node(void *data);
T_NODE *BT_insert_node(T_NODE *root, void *data);
T_NODE *BT_get_root(void);
size_t BT_get_node_size(void);
void BT_display_nodes(T_NODE *node);
void *BT_delete_node(T_NODE *root, void *data, int delete_data);
void BT_delete_tree(T_NODE *root, int delete_data);

#endif