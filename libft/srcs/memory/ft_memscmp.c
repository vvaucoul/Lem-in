/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memscmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:30:40 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:36:21 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memscmp(const void *ptr, const void *ptr_cmp, size_t len, size_t start)
{
    unsigned char *tmp_ptr = (unsigned char *)ptr;
    unsigned char *tmp_cmp = (unsigned char *)ptr_cmp;

    while (start--)
    {
        ++tmp_ptr;
        ++tmp_cmp;
        --len;
    }
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