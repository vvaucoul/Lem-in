/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:32:42 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:40:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putsarray(const char **array)
{
    if (!array)
        return;
    for (size_t i = 0; array[i]; i++)
        ft_putendl(array[i]);
}