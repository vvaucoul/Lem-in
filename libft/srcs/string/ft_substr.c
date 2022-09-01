/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:08:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:14:36 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char *str, size_t start, size_t len)
{
    char *new_str = NULL;
    size_t j = 0;

    if (!str)
        return (NULL);
    if (len > ft_strlen(str) || start > ft_strlen(str))
        return (str);
    if (!(new_str = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    for (size_t i = start; str[i] && i < len; ++i)
    {
        new_str[j] = str[i];
        ++j;
    }
    free(str);
    return (new_str);
}