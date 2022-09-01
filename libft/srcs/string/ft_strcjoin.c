/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:35:47 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 14:38:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcjoin(char *str, char c)
{
    char *new_str = NULL;
    size_t len;

    if (!str)
    {
        if (!(new_str = ft_calloc(sizeof(char), 2)))
            return (NULL);
        new_str[0] = c;
        return (new_str);
    }
    else
    {
        len = ft_strlen(str);
        if (!(new_str = ft_calloc(sizeof(char), len + 2)))
            return (NULL);
        ft_memcpy(new_str, str, len);
        new_str[len] = c;
    }
    return (new_str);
}