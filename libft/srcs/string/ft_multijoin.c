/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:52:50 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 13:58:39 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_multijoin(const char **array)
{
    char *new_str = NULL;
    size_t i = 0;

    if (!array)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_asize(array))))
        return (NULL);
    while (array[i])
    {
        if (!(new_str = ft_fstrjoin(new_str, array[i])))
            return (NULL);
        ++i;
    }
    return (new_str);
}