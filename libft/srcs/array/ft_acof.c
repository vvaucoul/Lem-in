/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:08:50 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 14:11:44 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

bool ft_acof(const char **array, const char *str)
{
    if (!array || !str)
        return (false);
    for (size_t i = 0; array[i]; ++i)
    {
        if (!ft_strcmp(array[i], str))
            return (true);
    }
    return (false);
}