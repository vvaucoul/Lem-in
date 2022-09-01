/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:23:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 14:27:33 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strncpy(const char *str, size_t len)
{
    char *new_str;

    if (!str)
        return (NULL);
    if (ft_strlen(str) < len)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    for (size_t i = 0; str[i] && i < len; ++i)
        new_str[i] = str[i];
    return (new_str);
}