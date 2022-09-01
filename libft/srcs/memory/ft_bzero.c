/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:47:25 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 01:48:32 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_bzero(void *ptr, size_t len)
{
    unsigned char *tmp = ptr;

    while (len)
    {
        *(tmp++) = 0;
        --len;
    }
    return (ptr);
}