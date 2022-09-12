/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:27:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/09 12:31:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ai-utils.h>

/*******************************************************************************
 *                                 AI - UTILS                                  *
 ******************************************************************************/

bool __utils_check_end(void)
{
    const int __end_room_id = __room_get_end_room()->id;

    for (int i = 0; i < ANT_COUNT(); i++)
    {
        if (GET_ANT(i).current_room->id != __end_room_id)
            return (false);
    }
    return (true);
}

int __return_error(const char *str, int error)
{
    write(2, COLOR_LIGHT_RED "Error: " COLOR_RESET, 16);
    write(2, COLOR_LIGHT_WHITE, ft_strlen(COLOR_LIGHT_WHITE));
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (error);
}