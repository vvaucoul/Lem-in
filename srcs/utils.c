/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:01:16 by mle-faou          #+#    #+#             */
/*   Updated: 2022/07/05 18:14:33 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int ft_strstr(char *s1, char *s2) {
    int i;
    int j;

    i = 0;
    while (s1[i])
    {
        j = 0;
        while (s2[j] && s1[i + j] == s2[j])
            j++;
        if (!s2[j])
            return (i);
        i++;
    }
    return (-1);
}

// int ft_strncmp(char *s1, char *s2, int n) {
//     int i;

//     i = 0;
//     while (s1[i] && s2[i] && i < n)
//         if (s1[i] != s2[i])
//             break;
//         else
//             i++;
//     return (s1[i] - s2[i]);
// }

// int ft_strcmp(char *s1, char *s2) {
//     if (ft_strlen(s1) > ft_strlen(s2))
//         return (ft_strncmp(s1, s2, ft_strlen(s1)));
//     return (ft_strncmp(s1, s2, ft_strlen(s2)));
// }

// int ft_strlen(char *str) {
//     int i;

//     i = 0;
//     while (str[i])
//         i++;
//     return (i);
// }

// char *ft_strncpy(char *dest, char *src, int n) {
//     int i = 0;
//     while (i < n && src[i])
//     {
//         dest[i] = src[i];
//         i++;
//     }
//     while (i < n)
//     {
//         dest[i] = '\0';
//         i++;
//     }
//     return (dest);
// }

// char **ft_split(char *str, char *separator) {
//     char **tab;
//     int j = 0;
//     int k = 0;

//     int tab_size = 1;
//     for (int i = 0; str[i]; i++) {
//         printf("split %d:[%s], checking next as %d:[%s]\n", i, str + i, i + ft_strlen(separator), str + (i + ft_strlen(separator)));
//         if (ft_strncmp(str + i, separator, ft_strlen(separator)) == 0 && str[i + ft_strlen(separator)]) {
//             printf("found\n");
//             tab_size++;
//             i += ft_strlen(separator) + 1;
//         }
//     }
//     printf("tab_size: %d\n", tab_size);

//     int i = 0;
//     tab = malloc(sizeof(char *) * (ft_strlen(str) + 1));
//     while (str[i])
//     {
//         if (ft_strstr(str + i, separator) == i)
//         {
//             tab[j] = malloc(sizeof(char) * (i - k + 1));
//             ft_strncpy(tab[j], str + k, i - k);
//             tab[j][i - k] = '\0';
//             j++;
//             k = i + ft_strlen(separator);
//         }
//         i++;
//     }
//     tab[j] = malloc(sizeof(char) * (i - k + 1));
//     ft_strncpy(tab[j], str + k, i - k);
//     tab[j][i - k] = '\0';
//     tab[j + 1] = NULL;
//     return (tab);
// }
