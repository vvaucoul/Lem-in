/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:06:21 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:31:45 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ai-utils.h"
#include "../../includes/graphic.h"

/*******************************************************************************
 *                                    ANTS                                     *
 ******************************************************************************/

/* Initialize ants */
int __ants_init(void)
{
    if (!(g_ants = malloc(sizeof(ANT) * ANT_COUNT())))
        exit(__return_error("Ants malloc failed", 1));
    for (int i = 0; i < ANT_COUNT(); i++)
    {
        const int x = __room_get_start_room()->x;
        const int y = __room_get_start_room()->y;

        GET_ANT(i).id = i;
        GET_ANT(i).x = x;
        GET_ANT(i).y = y;
        GET_ANT(i).moved = false;
        GET_ANT(i).current_room = __room_get_start_room();
    }

    /* Init Graphic Ants */
    add_turn(g_ants);
    return (0);
}

/* Free ants */
int __ants_free(void)
{
    if (g_ants)
    {
        free(g_ants);
        g_ants = NULL;
    }
    return (0);
}