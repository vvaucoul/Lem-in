/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:24:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:27:14 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int skip_useless_char(const char *str)
{
    int i;

    i = 0;
    while (str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\v' || str[i] == '\r' ||
           str[i] == '\f' || str[i] == ' ')
        ++i;
    return (i);
}

int ft_atoi(const char *str)
{
    int result = 0;
    bool isneg = false;
    size_t i;

    i = skip_useless_char(str);
    if (str[i] == '-' || str[i] == '+')
    {
        isneg = str[i] == '-' ? true : false;
        ++i;
    }
    while (str[i] && ft_isdigit(str[i]))
    {
        result = result * 10 + str[i] - 48;
        ++i;
    }
    result *= (isneg == 1 ? -1 : 1);
    return (result);
}
