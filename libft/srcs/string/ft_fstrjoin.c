/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:35:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:46:01 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_fstrjoin(char *str, const char *join)
{
    char *new_str = NULL;

    if (!(new_str = ft_strjoin(str, join)))
        return (NULL);
    free(str);
    return (new_str);
}