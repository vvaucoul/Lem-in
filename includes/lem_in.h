/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:54:56 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/18 14:51:26 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../libft/includes/libft.h"

// gnl
#define BUFFER_SIZE 1024

#define PARSER_VERBOSE 0
#define PARSER_MAP 0

// gnl.c
int get_next_line(int fd, char **line);

typedef enum room_type
{
    NORMAL,
    START,
    END
} t_room_type;

typedef struct s_room t_room;

struct s_room
{
    int id;
    t_room_type type;
    char *name;
    int x;
    int y;
    t_room **links;
};

typedef struct s_gameinfo
{
    t_room **map;
    int ant_count;
} t_gameinfo;

extern t_gameinfo g_gameinfo;

// parser.c
void init_struct(void);
int free_struct(void);
void print_map_config(void);
int parser(void);

// utils.c
int ft_strstr(char *s1, char *s2);

// map.c
int get_room_count(void);
int get_room_links_count(int room_id);
int get_room_id(char *name);
t_room *get_room(int room_id);
int get_link_id(int origin_id, int dest_id);
t_room *get_start_room(void);
t_room *get_end_room(void);
int are_room_coords_used(int x, int y);

float get_distance(t_room *room1, t_room *room2);
float get_largest_distance(void);
float get_smallest_distance(void);
t_room *get_left_most_room(void);
t_room *get_right_most_room(void);
t_room *get_top_most_room(void);
t_room *get_bottom_most_room(void);

int add_room(char *name, char *x_str, char *y_str, t_room_type type);
int add_link(char *room1, char *room2);

t_room *get_room(int room_id);
t_room *get_start_room(void);
t_room *get_end_room(void);

#endif /* LEM_IN_H */
