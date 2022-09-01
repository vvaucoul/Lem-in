/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:25:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:42:27 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_acpy(const char **arr)
{
    char **new_array = NULL;

    if (!arr)
        return (NULL);
    if (!(new_array = ft_calloc(sizeof(char * ), ft_asize((const char **)arr) + 1)))
        return (NULL);
    for (size_t i = 0; arr[i]; ++i)
    {
        new_array[i] = ft_strcpy(arr[i]);
        new_array[i + 1] = NULL;
    }
    return (new_array);
}