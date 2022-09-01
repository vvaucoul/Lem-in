/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:24:31 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:28:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *ptr, const void *ptr_cmp, size_t len)
{
    unsigned char *tmp_ptr = (unsigned char *)ptr;
    unsigned char *tmp_cmp = (unsigned char *)ptr_cmp;

    while (--len)
    {
        if (*tmp_ptr != *tmp_cmp)
            return (*tmp_ptr - *tmp_cmp);
        else
        {
            ++tmp_ptr;
            ++tmp_cmp;
        }
    }
    return (0);
}