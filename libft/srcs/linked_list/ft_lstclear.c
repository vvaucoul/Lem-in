/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:22:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 20:24:08 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstclear(t_list **lst, void (*f)(void *))
{
    t_list *tmp = *lst;
    t_list *previous = NULL;

    if (!lst)
        return;
    while (tmp)
    {
        previous = tmp;
        tmp = tmp->next;
        ft_lstdelone(previous, f);
    }
    *lst = NULL;
}