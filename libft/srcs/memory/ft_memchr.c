/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:37:10 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:40:11 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *ptr, int value, size_t len)
{
    unsigned char *tmp_ptr = (unsigned char *)ptr;

    while (--len)
    {
        if (*tmp_ptr == value)
            return (tmp_ptr);
        else
            ++tmp_ptr;
    }
    return (NULL);
}