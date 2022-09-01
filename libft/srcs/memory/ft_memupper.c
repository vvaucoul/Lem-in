/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:09:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 02:12:40 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memupper(void *ptr, size_t len)
{
    unsigned char *tmp_ptr = ptr;

    while (len--)
    {
        if (ft_islower(*tmp_ptr))
        {
            *(tmp_ptr) = ft_toupper(*tmp_ptr);
            (tmp_ptr++);
        }
    }
    return (ptr);
}