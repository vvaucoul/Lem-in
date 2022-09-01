/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:20:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:25:46 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *str, int c)
{
    char *tmp;
    if (!str)
        return (NULL);
    tmp = (char *)str;
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] == c)
            return (tmp);
        ++tmp;
    }
    if (!c)
        return (tmp);
    return (NULL);
}