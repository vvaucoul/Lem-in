/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lents.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:43:21 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:54:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_lents(const char *str, const char *cmp)
{
    size_t len = 0;

    if (!str || !cmp)
        return (0);

    len = ft_strlen(cmp);
    for (size_t i = 0; str[i]; ++i)
    {
        if (!ft_strncmp(&str[i], cmp, len))
            return (i);
    }
    return (ft_strlen(str));
}