/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multifree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:30:15 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 01:34:15 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_multifree(void **ptrs)
{
    if (!ptrs)
        return;
    for (size_t i = 0; ptrs[i]; ++i)
        free(ptrs[i]);
}