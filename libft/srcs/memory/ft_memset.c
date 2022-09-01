/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:38:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 01:41:03 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memset(void *ptr, int c, size_t len)
{
    unsigned char *tmp = (unsigned char *)ptr;

    while (len--)
        *(tmp++) = (unsigned char)c;
    return (ptr);
}