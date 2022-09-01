/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:55:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 18:06:56 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrep(char *src, const char *pat, const char *new_pat)
{
    char *new_str = NULL;
    size_t len;

    if (!pat || !new_pat || !src)
        return (NULL);
    len = ft_strlen(src);
    if (!(new_str = ft_calloc(sizeof(char), len + ft_strlen(new_pat) + 1)))
        return (NULL);
    if (ft_scof(src, pat) == false)
        return (NULL);
    for (size_t i = 0; src[i]; ++i)
    {
        if (!ft_strncmp(&src[i], pat, ft_strlen(pat)))
        {
            new_str = ft_fstrjoin(new_str, new_pat);
            i += ft_strlen(pat) - 1;
        }
        else
            new_str = ft_fstrcjoin(new_str, src[i]);
    }
    free(src);
    src = new_str;
    return (new_str);
}