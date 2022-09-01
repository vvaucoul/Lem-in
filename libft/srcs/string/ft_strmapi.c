/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:16:56 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:18:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
    char *new_str;
    int i;

    if (!str)
        return (NULL);
    i = 0;
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    while (str[i])
    {
        new_str[i] = (*f)(i, str[i]);
        ++i;
    }
    return (new_str);
}
