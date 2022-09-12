/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_ggc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:44:56 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:31:36 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai.h>

void **__ggc_ek_ptrs;
static int __current_index = 0;

/*******************************************************************************
 *                         GLOBAL GARBAGE COLLECTOR EK                         *
 ******************************************************************************/

int __add_gcc_ek(void *ptr)
{
    if (!__ggc_ek_ptrs)
    {
        if (!(__ggc_ek_ptrs = (void **)malloc((sizeof(void *) * 2))))
            exit(__return_error("Global Garbage Collector malloc failed", 1));
    }
    else
    {
        if (!(__ggc_ek_ptrs = (void **)realloc(__ggc_ek_ptrs, sizeof(void *) * (__current_index + 1))))
            exit(__return_error("Global Garbage Collector realloc failed", 1));
    }
    __ggc_ek_ptrs[__current_index] = ptr;
    ++__current_index;
    return (true);
}

void __free_gcc_ek(void)
{
    for (int i = 0; i < __current_index; i++)
    {
        if (__ggc_ek_ptrs[i])
        {
            free(__ggc_ek_ptrs[i]);
        }
    }
    free(__ggc_ek_ptrs);
}