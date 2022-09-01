/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:53:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 13:56:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_asize(const char **array)
{
    size_t i = 0, j = 0;
    size_t max_x = 0;

    if (!array)
        return (0);
    while (array[i])
    {
        while (array[i][j])
            ++j;
        if (j > max_x)
            max_x = j;
        ++i;
    }
    return ((i + 1) * (max_x + 1));
}