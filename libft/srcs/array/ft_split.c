/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:42:54 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:48:59 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char **assign(char **tab, const char *str, char del)
{
    size_t coords[2] = {0, 0};

    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] != del)
        {
            tab[coords[1]][coords[0]] = str[i];
            ++coords[0];
        }
        else
        {
            coords[0] = 0;
            coords[1]++;
            if (!(tab[coords[1]] = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
                return (NULL);
        }
    }
    tab[coords[1] + 1] = NULL;
    return (tab);
}

char **ft_split(const char *str, char del)
{
    char **tab = NULL;

    if (!str)
        return (NULL);
    if (!(tab = ft_calloc(sizeof(char *), ft_strlen(str) + 1)))
        return (NULL);
    if (!(tab[0] = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    return (assign(tab, str, del));
}
