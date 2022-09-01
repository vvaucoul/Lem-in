/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lentc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:39:26 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:55:24 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_lentc(const char *str, char c)
{
    if (!str)
        return (0);
    if (!ft_ccof(c, str))
        return (0);
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] == c)
            return (i);
    }
    return (ft_strlen(str));
}