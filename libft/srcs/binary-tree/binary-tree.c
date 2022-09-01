/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary-tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:15 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 11:45:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/binary-tree.h"

T_BT _g_bt = {NULL, 0};

T_NODE *BT_new_node(void *data)
{
    T_NODE *node = (T_NODE *)malloc(sizeof(T_NODE));

    if (!node)
        return (NULL);
    else
    {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        ++_g_bt.node_size;
        return (node);
    }
}

T_NODE *BT_insert_node(T_NODE *root, void *data)
{
    if (root == NULL)
        return (BT_new_node(data));
    else if (data < root->data)
        root->left = BT_insert_node(root->left, data);
    else if (data > root->data)
        root->right = BT_insert_node(root->right, data);
    return (root);
}

static T_NODE *get_min(T_NODE *node)
{
    T_NODE *current = node;

    while (current && current->left)
        current = current->left;
    return (current);
}

void *BT_delete_node(T_NODE *root, void *data, int delete_data)
{
    T_NODE *tmp;

    if (root == NULL)
        return (NULL);
    else if (data < root->data)
        root->left = BT_delete_node(root->left, data, delete_data);
    else if (data > root->data)
        root->right = BT_delete_node(root->right, data, delete_data);
    else
    {
        if (root->left == NULL)
        {
            tmp = root->right;
            if (delete_data)
                free(root->data);
            free(root);
            --_g_bt.node_size;
            return (tmp);
        }
        else if (root->right == NULL)
        {
            tmp = root->left;
            if (delete_data)
                free(root->data);
            free(root);
            --_g_bt.node_size;
            return (tmp);
        }
        else
        {
            tmp = get_min(root->right);
            root->data = tmp->data;
            root->right = BT_delete_node(root->right, tmp->data, delete_data);
        }
    }
    return (root);
}

void BT_delete_tree(T_NODE *root, int delete_data)
{
    if (root == NULL)
        return ;
    BT_delete_tree(root->left, delete_data);
    BT_delete_tree(root->right, delete_data);
    if (delete_data)
        free(root->data);
    free(root);
    root = NULL;
    --_g_bt.node_size;
}

T_NODE *BT_get_root(void)
{
    return (_g_bt.root);
}
size_t BT_get_node_size(void)
{
    return (_g_bt.node_size);
}

void BT_display_nodes(T_NODE *node)
{
    if (node != NULL)
    {
        BT_display_nodes(node->left);
        printf("%p\n", node->data);
        BT_display_nodes(node->right);
    }
}