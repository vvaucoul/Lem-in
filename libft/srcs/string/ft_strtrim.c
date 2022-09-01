/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:58:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 13:37:53 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim(char *str)
{
    if (!str)
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
    {
        while (ft_isspace(str[i]))
            ft_memmove((char *)&str[i], (char *)&str[i + 1], ft_strlen(str) - i);
    }
    return (str);
}