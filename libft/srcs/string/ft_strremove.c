/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:10:10 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 15:14:50 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strremove(const char *str, char c)
{
    char *new_str = NULL;
    size_t j = 0;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] != c)
        {
            new_str[j] = str[i];
            ++j;
        }
    }
    free((char *)str);
    return (new_str);
}