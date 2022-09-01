/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:49:29 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:53:24 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncmp(const char *str, const char *str2, size_t len)
{
    unsigned long int i;

    if (len == 0)
        return (0);
    i = 0;
    while (i < len && (unsigned char)str[i] == (unsigned char)str2[i])
    {
        if (((unsigned char)str[i] == 0 &&
             (unsigned char)str2[i] == 0) ||
            i == (len - 1))
            return (0);
        ++i;
    }
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}
