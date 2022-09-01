/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsrm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:17:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 10:20:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memsrm(void *ptr, char *str, size_t len)
{
    unsigned char *tmp_ptr = ptr;
    size_t max_len = len;
    while (len--)
    {
        if (ft_ccof(tmp_ptr[len], str) == true)
        {
            for (size_t i = len; i < max_len; ++i)
            {
                tmp_ptr[i] = tmp_ptr[i + 1];
            }
        }
    }
    return (ptr);
}
