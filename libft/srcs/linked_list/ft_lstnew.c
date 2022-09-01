/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:15:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 20:34:03 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstnew(void *data)
{
    t_list *new;

    if (!(new = malloc(sizeof(t_list))))
        return (NULL);
    new->data = data;
    new->next = NULL;
    return (new);
}