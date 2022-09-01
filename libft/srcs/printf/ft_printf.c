/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 00:59:06 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:25:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int display_case(t_printf *tfp, char c)
{
    if (c == 'd' || c == 'i')
    {
        int tmp = va_arg(tfp->list, int);
        ft_putnbr(tmp);
    }
    else if (c == 's')
    {
        char *tmp = va_arg(tfp->list, char *);
        if (!tmp)
            ft_putstr("null");
        else
            ft_putstr(tmp);
    }
    return (0);
}

static ssize_t parse(t_printf *ptf)
{
    size_t i = 0;

    if (!ptf->str)
        return (0);
    for (; ptf->str[i]; ++i)
    {
        if (ptf->str[i] == '%')
        {
            display_case(ptf, ptf->str[i + 1]);
            ++i;
        }
        else
            ft_putchar(ptf->str[i]);
    }
    return (0);
}

int ft_printf(const char *str, ...)
{
    t_printf ptf;

    ptf.str = (char *)str;
    va_start(ptf.list, str);
    if (parse(&ptf))
        return (1);
    va_end(ptf.list);
    return (0);
}