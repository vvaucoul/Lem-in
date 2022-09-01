/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sncof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:15:15 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:58:42 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool ft_sncof(const char *str, const char *cmp, size_t len)
{
    if (!str || !cmp)
        return (false);
    for (size_t i = 0; str[i] && i < len; ++i)
    {
        for (size_t j = 0; cmp[j]; ++j)
        {
            if (str[i] == cmp[j])
                return (true);
        }
    }
    return (false);
}