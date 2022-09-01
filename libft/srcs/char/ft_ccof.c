/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ccof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:13:44 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 02:15:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool ft_ccof(char c, const char *str)
{
    if (!str)
        return (false);
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] == c)
            return (true);
    }
    return (false);
}