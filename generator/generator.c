/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:01:07 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/14 16:50:30 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This program is used to generate a random map for the lem-in game.
** @param: int argc, char **argv
** @param: <int> -> Number of rooms
** @param: <int> -> Number ants
** @param: <char *> -> filename
**
** Warning: Start and End rooms can be not connected togheter.
*/

#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "../libft/includes/libft.h"

int __fd = -1;

static int create_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Error: %s\n", strerror(errno));
        return (0);
    }
    return (fd);
}

int main(int argc, const char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <nb_rooms> <nb_ants> <filename>\n", argv[0]);
        return (0);
    }
    if ((__fd = create_file(argv[3])) == 0)
        return (1);
    srand(time(NULL));
    
    dprintf(__fd, "%d\n", ft_atoi(argv[1]));
    dprintf(__fd, "%s\n", "##start");
    dprintf(__fd, "start 0 1\n");
    dprintf(__fd, "%s\n", "##end");
    dprintf(__fd, "end 1 0\n");

    int node = ft_atoi(argv[1]);
    int ran = 0;
    int i = 0;

    while (i < node)
        dprintf(__fd, "%1$d %1$d %1$d\n", i++);
    i = 0;
    while (i < node)
    {
        while (rand() % 2)
        {
            ran = rand() % node;
            while (ran == i)
                ran = rand() % node;
            dprintf(__fd, "%d-%d\n", i, ran);
        }
        ran = rand() % node;
        while (ran == i)
            ran = rand() % node;
        dprintf(__fd, "%d-%d\n", i++, ran);
    }
    i = 0;
    dprintf(__fd, "start-");
    dprintf(__fd, "%d\n", rand() % node);
    while (rand() % 2)
    {
        dprintf(__fd, "start-");
        dprintf(__fd, "%d\n", rand() % node);
    }
    dprintf(__fd, "end-");
    dprintf(__fd, "%d\n", rand() % node);
    while (rand() % 2)
    {
        dprintf(__fd, "end-");
        dprintf(__fd, "%d\n", rand() % node);
    }

    return (0);
}