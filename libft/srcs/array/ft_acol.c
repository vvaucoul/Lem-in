/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:38:07 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:38:22 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_acol(const char **array)
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
    return (max_x + 1);
}