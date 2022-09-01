/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:30:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:47:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(const char *str, const char *join)
{
    char *new_str = NULL;
    size_t i = 0, j = 0, length = 0;

    if (!str)
        return (NULL);
    if (!join)
        return ((char *)str);

    length = ft_strlen(str) + ft_strlen(join) + 1;
    if (!(new_str = ft_calloc(sizeof(char), length)))
        return (NULL);
    ft_bzero(new_str, length);
    for (; str[i]; ++i)
        new_str[i] = str[i];
    for (; join[j]; ++j)
        new_str[i + j] = join[j];
    return (new_str);
}