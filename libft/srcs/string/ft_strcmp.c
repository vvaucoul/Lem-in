/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:08:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:08:55 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int ft_strcmp(const char *str, const char *str2)
{
    unsigned int i;

    i = 0;
    while (str[i] && str[i] == str2[i])
        ++i;
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}
