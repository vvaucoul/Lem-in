/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strzap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:40:38 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 13:51:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strzap(char *str, const char *pat)
{
    size_t j = 0;
    char *new_str = NULL;

    if (!str || !pat)
        return (NULL);
    if (ft_strlen(str) < ft_strlen(pat))
        return (str);
    if (!ft_strsncmp(str, pat, 0, ft_strlen(pat)))
    {
        if (!(new_str = ft_calloc(sizeof(char), (ft_strlen(str) - ft_strlen(pat)) + 1)))
            return (NULL);
        for (size_t i = ft_strlen(pat); str[i]; ++i)
        {
            new_str[j] = str[i];
            ++j;
        }
        free(str);
        str = new_str;
        return (new_str);
    }
    return (str);
}