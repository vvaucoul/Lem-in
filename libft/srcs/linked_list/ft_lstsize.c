/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:13:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 20:14:42 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_lstsize(t_list *lst)
{
    size_t n = 0;
    t_list *tmp = lst;

    while (tmp)
    {
        ++n;
        tmp = tmp->next;
    }
    return (n);
}