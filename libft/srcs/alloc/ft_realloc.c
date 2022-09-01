/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:49:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 00:13:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t newsize)
{
    char *newptr;
    size_t cursize;

    if (!ptr)
        return (malloc(newsize));
    cursize = sizeof(ptr);
    if (newsize <= cursize)
        return (ptr);
    if ((newptr = malloc(newsize)) == NULL)
        return (NULL);
    else
        ft_memcpy(newptr, ptr, cursize);
    free(ptr);
    return (newptr);
}
