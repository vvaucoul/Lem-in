/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:11:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:12:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcpy(const char *str)
{
    char *new_str;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str))))
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
        new_str[i] = str[i];
    return (new_str);
}