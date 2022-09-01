/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:50:42 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 02:09:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memlower(void *ptr, size_t len)
{
    unsigned char *tmp_ptr = ptr;

    while (len--)
    {
        if (ft_isupper(*tmp_ptr))
        {
            *(tmp_ptr) = ft_tolower(*tmp_ptr);
            (tmp_ptr++);
        }
    }
    return (ptr);
}