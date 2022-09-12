/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:36:20 by mle-faou          #+#    #+#             */
/*   Updated: 2022/09/05 15:05:20 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void init_struct(void)
{
    g_gameinfo.map = NULL;
    g_gameinfo.ant_count = 0;
}

int free_struct(void)
{
    for (int i = 0; i < get_room_count(); i++)
    {
        free(g_gameinfo.map[i]->name);
        free(g_gameinfo.map[i]->links);
        free(g_gameinfo.map[i]);
    }
    free(g_gameinfo.map);
    return (1);
}

int get_ant_count(char *line)
{
    int nb = 0;
    for (int i = 0; line[i]; i++)
    {
        if (i > 8)
        {
            printf("Error: too many ants\n");
            return (-1);
        }
        if (line[i] >= '0' && line[i] <= '9')
            nb = nb * 10 + (line[i] - '0');
        else
            return (-1);
    }
    return (nb);
}

char *trim_line(char *line)
{
    int i = 0;
    while (line[i] && line[i] == ' ')
        i++;
    return (line + i);
}

int are_rooms_unconnected(void)
{
    int *connect_check_list;
    if (!(connect_check_list = malloc(sizeof(int) * get_room_count())))
    {
        printf("Error: malloc failed");
        return (1);
    }
    for (int i = 0; i < get_room_count(); i++)
        connect_check_list[i] = 0;
    if (get_start_room() == NULL)
    {
        printf("Error: no start room\n");
        return (1);
    }
    connect_check_list[get_start_room()->id] = 1;
    int did_something = 1;
    while (did_something == 1)
    {
        did_something = 0;
        for (int i = 0; i < get_room_count(); i++)
        {
            if (connect_check_list[i] == 1)
            {
                for (int j = 0; j < get_room_links_count(i); j++)
                {
                    if (connect_check_list[g_gameinfo.map[i]->links[j]->id] == 0)
                        connect_check_list[g_gameinfo.map[i]->links[j]->id] = 1;
                }
                connect_check_list[i] = 2;
                did_something = 1;
            }
            /// ??? maybe remove this
            if (i == get_room_count() - 1 && did_something == 0)
                break;
        }
    }
    if (connect_check_list[get_end_room()->id] != 2)
    {
        printf("Error: end room not connected to start\n");
        return (1);
    }
    for (int i = 0; i < get_room_count(); i++)
    {
        if (connect_check_list[i] != 2)
        {
            printf("Error: room '%s' not connected to start\n", get_room(i)->name);
            return (1);
        }
    }
    free(connect_check_list);
    return (0);
}

void print_all_rooms(void)
{
    for (int i = 0; i < get_room_count(); i++)
    {
        printf("%d: [%s] ##%d\n", i, g_gameinfo.map[i]->name, g_gameinfo.map[i]->type);
        // print all links
        if (g_gameinfo.map[i]->links == NULL)
            continue;
        for (int j = 0; g_gameinfo.map[i]->links[j]; j++)
        {
            printf("-%d->%d :[%s]\n", j, g_gameinfo.map[i]->links[j]->id, g_gameinfo.map[i]->links[j]->name);
        }
    }
}

void print_map_config(void)
{
    printf("%d\n", g_gameinfo.ant_count);
    for (int i = 0; i < get_room_count(); i++)
    {
        if (g_gameinfo.map[i]->type == START)
            printf("##start\n");
        else if (g_gameinfo.map[i]->type == END)
            printf("##end\n");
        printf("%s %d %d\n", g_gameinfo.map[i]->name, g_gameinfo.map[i]->x, g_gameinfo.map[i]->y);
    }
    for (int i = 0; i < get_room_count(); i++)
    {
        for (int j = 0; g_gameinfo.map[i]->links[j]; j++)
        {
            if (g_gameinfo.map[i]->links[j]->id > i)
                printf("%s-%s\n", g_gameinfo.map[i]->name, g_gameinfo.map[i]->links[j]->name);
        }
    }
}

int parser(void)
{
    init_struct();
    char *line = NULL;
    int line_num = 0;
    int next_room_type = 0; // 0: normal, 1: start, 2: end
    int parser_state = 0; // 0: nothing, 1: reading ant count, 2: reading room, 3: reading link,
    int gnl_ret = 0;
    do
    {
        gnl_ret = get_next_line(0, &line);
        if (gnl_ret == -1)
        {
            printf("Error: get_next_line failed\n");
            return (1);
        }
        line_num++;
        for (int i = 0; line[i]; i++)
        {
            if (line[i] == '#' && line[i + 1] == '#')
                i += 2;
            if (line[i] == '#' && line[i + 1] != '#')
            {
                line[i] = '\0';
                break;
            }
        }
        int start = 0;
        for (; line[start] == ' '; start++)
            ;
        int end = ft_strlen(line);
        if (end < start)
            end = start;
        for (; end > start && (line[end] == ' ' || line[end] == '\0'); end--)
            ;
        line = ft_substr(line, start, end + 1);
        if (PARSER_VERBOSE)
            printf("%d-> [%s], ##%d\n", line_num, line, next_room_type);
        if (ft_strlen(line) == 0)
        {
            free(line);
            continue;
        }
        if (line[0] == '#' && line[1] == '#')
        {
            next_room_type = 0;
            if (ft_strcmp(line, "##start") == 0)
                next_room_type = 1;
            else if (ft_strcmp(line, "##end") == 0)
                next_room_type = 2;
            else
                printf("Error: invalid command at line %d\n", line_num);
            free(line);
            continue;
        }
        int tmp = 0;
        if ((tmp = ft_strstr(line, " ")) != -1)
        {
            // room
            if (parser_state != 1 && parser_state != 2)
            {
                printf("Error: unexpected room declaration at line %d\n", line_num);
                free(line);
                return (free_struct());
            }
            parser_state = 2;
            int tmp2;
            if ((tmp2 = ft_strstr(line + tmp + 1, " ")) == -1)
            {
                printf("Error: not enough spaces at line %d\n", line_num);
                free(line);
                return (free_struct());
            }
            tmp += tmp2;
            if (ft_strstr(line + tmp + 2, " ") != -1)
            {
                printf("Error: too many spaces at line %d\n", line_num);
                free(line);
                return (free_struct());
            }
            char **split = NULL;
            if (!(split = malloc(sizeof(char *) * 4)))
            {
                printf("Error: malloc failed\n");
                free(line);
                return (free_struct());
            }
            if (!(ft_strsplit(line, split, " ")))
            {
                printf("Error: ft_strsplit failed\n");
                free(split[0]);
                free(split[1]);
                free(split[2]);
                free(split);
                free(line);
                return (free_struct());
            }
            if (add_room(split[0], split[1], split[2], next_room_type))
            {
                printf(" at line %d\n", line_num);
                free(split[0]);
                free(split[1]);
                free(split[2]);
                free(split);
                free(line);
                return (free_struct());
            }
            // do not free split[0] or name will be corrupted
            free(split[1]);
            free(split[2]);
            free(split);
            next_room_type = 0;
            free(line);
            continue;
        }
        if ((tmp = ft_strstr(line, "-")) != -1)
        {
            // link
            if (parser_state != 2 && parser_state != 3)
            {
                printf("Error: unexpected link declaration at line %d\n", line_num);
                free(line);
                return (free_struct());
            }
            parser_state = 3;
            if (ft_strstr(line + tmp + 1, "-") != -1)
            {
                printf("Error: too many '-' at line %d\n", line_num);
                free(line);
                return (free_struct());
            }
            char **split = NULL;
            if (!(split = malloc(sizeof(char *) * 3)))
            {
                printf("Error: malloc failed\n");
                free(line);
                return (free_struct());
            }
            if (!(ft_strsplit(line, split, "-")))
            {
                printf("Error: ft_strsplit failed\n");
                free(split);
                free(line);
                return (free_struct());
            }
            if (add_link(split[0], split[1]))
            {
                printf(" at line %d\n", line_num);
                free(split[0]);
                free(split[1]);
                free(split);
                free(line);
                return (free_struct());
            }
            free(split[0]);
            free(split[1]);
            free(split);
            free(line);
            next_room_type = 0;
            continue;
        }
        next_room_type = 0;
        if (parser_state != 0 && parser_state != 1)
        {
            printf("Error: unexpected ant count declaration at line %d\n", line_num);
            free(line);
            return (free_struct());
        }
        if (g_gameinfo.ant_count != 0)
        {
            printf("Error: ant count redefinition at line %d\n", line_num);
            free(line);
            return (free_struct());
        }
        g_gameinfo.ant_count = get_ant_count(line);
        if (g_gameinfo.ant_count == -1)
        {
            printf("Error: invalid ant count at line %d\n", line_num);
            free(line);
            return (free_struct());
        }
        parser_state = 1;
        free(line);
    } while (gnl_ret > 0);
    if (PARSER_MAP)
        print_all_rooms();
    int start_check = 0;
    int end_check = 0;
    for (int i = 0; i < get_room_count(); i++)
    {
        if (g_gameinfo.map[i]->type == 1)
            start_check++;
        if (g_gameinfo.map[i]->type == 2)
            end_check++;
    }
    if (start_check < 1)
    {
        printf("Error: no start room\n");
        return (free_struct());
    }
    if (start_check > 1)
    {
        printf("Error: multiple start rooms\n");
        return (free_struct());
    }
    if (end_check < 1)
    {
        printf("Error: no end room\n");
        return (free_struct());
    }
    if (end_check > 1)
    {
        printf("Error: multiple end rooms\n");
        return (free_struct());
    }
    if (g_gameinfo.ant_count == 0)
    {
        printf("Error: no ant\n");
        return (free_struct());
    }
    if (are_rooms_unconnected())
    {
        printf("Error: rooms are not connected\n");
        return (free_struct());
    }
    return (0);
}

// during parsing :
// check maybe config order                 good
// check comments next to actual commend    good
// check if reading last line               good

// in ants :
// check if oveflow                         good
// can define ant count only one time       good

// in rooms :
// check if room name already exists        good
// check if room coords already are used    good
// check if room starts with 'L'            good

// in links :
// check if link links two existing rooms   good
// check if link already exists             good

// before the end :
// check if start and end exist             good
// check if start and end are connected     good
// check if all rooms are connected         good
// check if ant-count > 0                   good
// free all malloced stuff                  good
