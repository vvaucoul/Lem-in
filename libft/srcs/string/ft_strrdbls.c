/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrdbls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:15:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 15:19:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrdbls(const char *str, char c)
{
    char *new_str = NULL;
    size_t j = 0;
    int pass = 0;

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
            pass = 0;
        }
        else
        {
            if (pass == 0)
            {
                new_str[j] = str[i];
                ++j;
            }
            ++pass;
        }
    }
    free((char *)str);
    return (new_str);
}