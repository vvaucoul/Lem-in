/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:20:59 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:24:10 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void **ft_aalloc(size_t size, size_t size_x, size_t size_y)
{
    void **tab;
    
    if (!(tab = ft_calloc(size, ((size_x + 1) * (size_y + 1)) + 1)))
        return (NULL);
    for (size_t i = 0; i < size_y; ++i)
    {
        if (!(tab[i] = ft_calloc(size, (size_x + 1))))
            return (NULL);
        tab[i + 1] = NULL;
    }
    return (tab);
}