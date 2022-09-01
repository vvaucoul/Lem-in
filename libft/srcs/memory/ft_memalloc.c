/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:55:12 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:00:15 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memalloc(void **dst, const void *ref, size_t size, size_t len)
{
    if (!ref)
        return (NULL);
    if (!(*dst = ft_calloc(size, len)))
        return (NULL);
    ft_memcpy(*dst, ref, len);
    return (*dst);
}