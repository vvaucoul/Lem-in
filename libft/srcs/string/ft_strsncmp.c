/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:48:50 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:53:14 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strsncmp(const char *str, const char *cmp, size_t start, size_t len)
{
    if (!len)
        return (0);
    if (!str || !cmp)
        return (0);
    if (start > ft_strlen(str))
        return (0);

    size_t i = start;
    for (; str[i] == cmp[i]; ++i)
    {
        if ((!str[i] && !cmp[i]) || i == (len - 1))
            return (0);
    }
    return (str[i] - cmp[i]);
}