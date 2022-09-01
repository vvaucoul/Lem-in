/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcrm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:12:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:16:56 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcrm(void *ptr, char c, size_t len)
{
    unsigned char *tmp_ptr = ptr;
    size_t max_len = len;
    while (len--)
    {
        if (tmp_ptr[len] == c)
        {
            for (size_t i = len; i < max_len; ++i) {
                tmp_ptr[i] = tmp_ptr[i + 1];
            }
        }
    }
    return (ptr);
}