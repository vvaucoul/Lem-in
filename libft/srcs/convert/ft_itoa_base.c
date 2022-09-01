/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:30:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:30:20 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char *ft_itoa_neg_base(int nb, int base)
{
    unsigned int tmp_nb;
    char *str_base;
    char *final_nb;
    int nb_count;
    int i;

    tmp_nb = nb;
    str_base = ft_strdup("0123456789abcdef");
    nb_count = 8;
    final_nb = ft_strdup("ffffffff");
    i = 1;
    while (tmp_nb)
    {
        final_nb[nb_count - i] = str_base[tmp_nb % base];
        tmp_nb /= base;
        ++i;
    }
    free(str_base);
    return (final_nb);
}

static int ft_intlen_base(int nb, int base)
{
    int len;

    len = 0;
    while (nb)
    {
        nb /= base;
        ++len;
    }
    return (len);
}

static char *ft_calcul_base(int nb, int base, int is_neg)
{
    char *str_base;
    char *final_nb;
    int nb_count;
    int i;

    str_base = ft_strdup("0123456789abcdef");
    nb_count = ft_intlen_base(nb, base);
    nb_count += is_neg == 1 ? 1 : 0;
    final_nb = malloc(sizeof(char) * nb_count + 1);
    i = 1;
    is_neg == 1 ? (final_nb[0] = '-') : 0;
    while (nb)
    {
        final_nb[nb_count - i] = str_base[nb % base];
        nb /= base;
        ++i;
    }
    final_nb[nb_count] = '\0';
    free(str_base);
    return (final_nb);
}

char *ft_itoa_base(int nb, int base)
{
    int is_neg;

    is_neg = 0;
    if (base < 2 || base > 16)
        return (0);
    if (base == 10 && nb == -2147483648)
        return ("-2147483648");
    if (nb == 0)
        return ("0");
    if (nb < 0)
    {
        return (ft_itoa_neg_base(nb, base));
        nb *= -1;
        if (base == 10)
            is_neg = 1;
    }
    else
        is_neg = 0;
    return (ft_calcul_base(nb, base, is_neg));
}
