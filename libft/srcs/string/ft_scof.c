/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:16:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:58:27 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool ft_scof(const char *str, const char *cmp)
{
    if (!str || !cmp)
        return (false);
    for (size_t i = 0; str[i]; ++i)
    {
        for (size_t j = 0; cmp[j]; ++j)
        {
            if (str[i] == cmp[j])
                return (true);
        }
    }
    return (false);
}