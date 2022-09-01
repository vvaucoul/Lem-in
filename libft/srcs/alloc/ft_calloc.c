/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:51:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:01:19 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_calloc(size_t size, size_t count)
{
    void *ptr = NULL;

    if (!(ptr = malloc(sizeof(size) * (count + 1))))
        return (NULL);
    ft_bzero(ptr, count + 1);
    return (ptr);
}