/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:55:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/07 20:10:07 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include "../includes/graphic.h"
#include "../includes/ai.h"

t_gameinfo g_gameinfo;
t_turn *g_turns;

int main(int argc, const char *argv[])
{
    init_struct();
    if (parser())
        return (1);
    print_map_config();
    g_turns = NULL;
    if (ai_main())
        return (1);
    if (argc == 2 && !ft_strcmp(argv[1], "-g"))
    {
        if (!ft_strcmp(argv[1], "-g"))
        {
            if (graphic())
            {
                free_struct();
                free_turns();
                return (1);
            }
        }
        else
        {
            ft_putstr("Usage: ./lem-in [-g]\n");
            return (1);
        }
    }
    free_struct();
    free_turns();
    return (0);
}