/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memshr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:40:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:45:41 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memshr(const void *ptr, const void *cmp, size_t len, size_t nb)
{
    unsigned char *tmp_ptr = (unsigned char *)ptr;
    unsigned char *tmp_cmp = (unsigned char *)cmp;

    size_t i = 0;
    while (--len)
    {
        if (!ft_memcmp(tmp_ptr, tmp_cmp, nb))
            return (tmp_ptr);
        else
        {
            ++i;
            ++tmp_ptr;
        }
    }
    return (NULL);
}