/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:05:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 15:02:15 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool add_string_to_words(char **words, char *str, size_t index)
{
    if (!(words[index] = ft_strdup(str)))
        return (false);
    words[index + 1] = NULL;
    free(str);
    str = NULL;
    return (true);
}

char *ft_strsplit(char *src, char **words, const char *sep)
{
    char *to_add = NULL;
    size_t j = 0;

    if (!src)
        return (NULL);
    if (!words)
        return (NULL);
    for (size_t i = 0; src[i]; ++i)
    {
        if (!ft_strsncmp(&src[i], sep, 0, ft_strlen(sep)))
        {
            if (to_add)
            {
                if (!(add_string_to_words(words, to_add, j)))
                    return (NULL);
                to_add = NULL;
                ++j;
                i += ft_strlen(sep) - 1;
            }
            else
                ++i;
        }
        else
            to_add = ft_fstrcjoin(to_add, src[i]);
    }
    if (to_add)
    {
        if (!(add_string_to_words(words, to_add, j)))
            return (NULL);
        to_add = NULL;
    }
    return (src);
}
