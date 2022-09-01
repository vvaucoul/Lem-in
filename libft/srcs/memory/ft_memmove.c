/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:04:55 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 13:07:57 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dest, const void *ptr, size_t len)
{
    unsigned char *tmp_dest;
    unsigned char *tmp_ptr;
    if (!ptr)
        return (NULL);

    tmp_dest = (unsigned char *)dest;
    tmp_ptr = (unsigned char *)ptr;
    while (len--)
    {
        *tmp_dest = *tmp_ptr;
        ++tmp_dest;
        ++tmp_ptr;
    }
    return (dest);
}