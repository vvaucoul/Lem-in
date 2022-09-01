/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:08:30 by mle-faou          #+#    #+#             */
/*   Updated: 2022/07/15 14:28:29 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int get_room_count(void) {
    if (g_gameinfo.map == NULL)
        return (0);
    int count;
    for (count = 0; g_gameinfo.map[count]; count++)
        ;
    return (count);
}

int get_room_links_count(int room_id) {
    if (g_gameinfo.map == NULL)
        return (0);
    if (g_gameinfo.map[room_id] == NULL)
        return (0);
    if (g_gameinfo.map[room_id]->links == NULL)
        return (0);
    int count;
    for (count = 0; g_gameinfo.map[room_id]->links[count]; count++)
        ;
    return (count);
}

int get_room_id(char *name) {
    if (g_gameinfo.map == NULL)
        return (-1);
    for (int i = 0; g_gameinfo.map[i]; i++) {
        // printf("get_room_id :%d[%s]/[%s]\n", i, g_gameinfo.map[i]->name, name);
        // printf("get_room_id :%d[%d]/[%s]\n", i, g_gameinfo.map[i]->id, name);
        if (ft_strcmp(g_gameinfo.map[i]->name, name) == 0)
            return (g_gameinfo.map[i]->id);
    }
    return (-1);
}

t_room *get_room(int room_id) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    if (g_gameinfo.map[room_id] == NULL)
        return (NULL);
    return (g_gameinfo.map[room_id]);
}

int get_link_id(int origin_id, int dest_id) {
    if (g_gameinfo.map == NULL)
        return (-1);
    if (g_gameinfo.map[origin_id] == NULL)
        return (-1);
    if (g_gameinfo.map[origin_id]->links == NULL)
        return (-1);
    for (int i = 0; g_gameinfo.map[origin_id]->links[i]; i++)
        if (g_gameinfo.map[origin_id]->links[i]->id == dest_id)
            return (i);
    return (-1);
}

t_room *get_start_room(void) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    for (int i = 0; g_gameinfo.map[i]; i++) {
        if (g_gameinfo.map[i]->type == START)
            return (g_gameinfo.map[i]);
    }
    return (NULL);
}

t_room *get_end_room(void) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    for (int i = 0; g_gameinfo.map[i]; i++)
        if (g_gameinfo.map[i]->type == END)
            return (g_gameinfo.map[i]);
    return (NULL);
}

int are_room_coords_used(int x, int y) {
    if (g_gameinfo.map == NULL)
        return (0);
    for (int i = 0; g_gameinfo.map[i]; i++)
        if (g_gameinfo.map[i]->x == x && g_gameinfo.map[i]->y == y)
            return (1);
    return (0);
}

float get_distance(t_room *room1, t_room *room2) {
    if (room1 == NULL || room2 == NULL)
        return (0);
    return (sqrt(pow(room1->x - room2->x, 2) + pow(room1->y - room2->y, 2)));
}

float get_largest_distance(void) {
    if (g_gameinfo.map == NULL)
        return (0);
    int max = 0;
    for (int i = 0; g_gameinfo.map[i]; i++) {
        for (int j = 0; g_gameinfo.map[j]; j++) {
            if (i == j)
                continue;
            int dist = get_distance(g_gameinfo.map[i], g_gameinfo.map[j]);
            if (dist > max)
                max = dist;
        }
    }
    return (max);
}

float get_smallest_distance(void) {
    if (g_gameinfo.map == NULL)
        return (0);
    int min = INT_MAX;
    for (int i = 0; g_gameinfo.map[i]; i++) {
        for (int j = 0; g_gameinfo.map[j]; j++) {
            if (i == j)
                continue;
            int dist = get_distance(g_gameinfo.map[i], g_gameinfo.map[j]);
            if (dist < min)
                min = dist;
        }
    }
    return (min);
}

t_room *get_left_most_room(void) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    t_room *left_most = g_gameinfo.map[0];
    for (int i = 0; g_gameinfo.map[i]; i++) {
        if (g_gameinfo.map[i]->x < left_most->x)
            left_most = g_gameinfo.map[i];
    }
    return (left_most);
}

t_room *get_right_most_room(void) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    t_room *right_most = g_gameinfo.map[0];
    for (int i = 0; g_gameinfo.map[i]; i++) {
        if (g_gameinfo.map[i]->x > right_most->x)
            right_most = g_gameinfo.map[i];
    }
    return (right_most);
}

t_room *get_top_most_room(void) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    t_room *top_most = g_gameinfo.map[0];
    for (int i = 0; g_gameinfo.map[i]; i++) {
        if (g_gameinfo.map[i]->y > top_most->y)
            top_most = g_gameinfo.map[i];
    }
    return (top_most);
}

t_room *get_bottom_most_room(void) {
    if (g_gameinfo.map == NULL)
        return (NULL);
    t_room *bottom_most = g_gameinfo.map[0];
    for (int i = 0; g_gameinfo.map[i]; i++) {
        if (g_gameinfo.map[i]->y < bottom_most->y)
            bottom_most = g_gameinfo.map[i];
    }
    return (bottom_most);
}

int add_room(char *name, char *x_str, char *y_str, t_room_type type) {
    if (name[0] == 'L') {
        printf("Error: room name cannot start with L");
        return (1);
    }
    for (int i = 0; name[i]; i++) {
        if ((name[i] < 'a' || name[i] > 'z') &&
            (name[i] < 'A' || name[i] > 'Z') &&
            (name[i] < '0' || name[i] > '9') &&
            name[i] != '_') {
            printf("Error: room name must be alnum and '_'");
            return (1);
        }
    }
    if (get_room_id(name) != -1) {
        printf("Error: room name already exists");
        return (1);
    }
    int x = 0;
    for (int i = 0; x_str[i]; i++) {
        if (x_str[i] < '0' || x_str[i] > '9') {
            printf("Error: room x must be numeric");
            return (1);
        }
        x = x * 10 + (x_str[i] - '0');
    }
    int y = 0;
    for (int i = 0; y_str[i]; i++) {
        if (y_str[i] < '0' || y_str[i] > '9') {
            printf("Error: room y must be numeric");
            return (1);
        }
        y = y * 10 + (y_str[i] - '0');
    }
    if (are_room_coords_used(x, y)) {
        printf("Error: room coords already used");
        return (1);
    }
    int room_count = get_room_count();
    // printf("add_room : room_count = %d\n", room_count);
    t_room *room;
    if (!(room = malloc(sizeof(t_room)))) {
        printf("Error: malloc failed");
        return (1);
    }
    room->id = room_count;
    room->type = type;
    room->name = name;
    room->x = x;
    room->y = y;
    room->links = NULL;
    t_room **new_map;
    if(!(new_map = malloc(sizeof(t_room *) * (room_count + 2)))) {
        printf("Error: malloc failed");
        return (1);
    }
    for (int i = 0; i < room_count; i++)
        new_map[i] = g_gameinfo.map[i];
    new_map[room_count] = room;
    new_map[room_count + 1] = NULL;
    free(g_gameinfo.map);
    g_gameinfo.map = new_map;
    // printf("add_room : new room name = [%s]\n", g_gameinfo.map[room_count]->name);
    return (0);
}

int add_link(char *room1, char *room2) {
    int room1_id = get_room_id(room1);
    if (room1_id == -1) {
        printf("Error: room1 name does not exist");
        return (1);
    }
    int room2_id = get_room_id(room2);
    if (room2_id == -1) {
        printf("Error: room2 name does not exist");
        return (1);
    }
    if (!(get_link_id(room1_id, room2_id))) {
        printf("Error: room1 and room2 are already linked");
        return (1);
    }
    //room1
    int room1_links_count = get_room_links_count(room1_id);
    t_room **new_room1_links;
    if(!(new_room1_links = malloc(sizeof(t_room *) * (room1_links_count + 2)))) {
        printf("Error: malloc failed");
        return (1);
    }
    for (int i = 0; i < room1_links_count; i++)
        new_room1_links[i] = g_gameinfo.map[room1_id]->links[i];
    new_room1_links[room1_links_count] = g_gameinfo.map[room2_id];
    new_room1_links[room1_links_count + 1] = NULL;
    free(g_gameinfo.map[room1_id]->links);
    g_gameinfo.map[room1_id]->links = new_room1_links;
    //room2
    int room2_links_count = get_room_links_count(room2_id);
    t_room **new_room2_links;
    if(!(new_room2_links = malloc(sizeof(t_room *) * (room2_links_count + 2)))) {
        printf("Error: malloc failed");
        return (1);
    }
    for (int i = 0; i < room2_links_count; i++)
        new_room2_links[i] = g_gameinfo.map[room2_id]->links[i];
    new_room2_links[room2_links_count] = g_gameinfo.map[room1_id];
    new_room2_links[room2_links_count + 1] = NULL;
    free(g_gameinfo.map[room2_id]->links);
    g_gameinfo.map[room2_id]->links = new_room2_links;
    return (0);
}
