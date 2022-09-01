/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bck-ai_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:48:54 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/07/15 22:25:02 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/old-ai.h"
#include <time.h>

ANT *g_ants;
EK g_ek = {NULL, 0};

// int __room_count = 0;

#define CLEAR_SCREEN() printf("\033[2J\033[1;1H")

/*******************************************************************************
 *                                    DEBUG                                    *
 ******************************************************************************/

static void __debug_wait_input(void)
{
    int c;
    int ret = 0;

    ret = read(1, &c, 1);
}

static void __debug_print_root(EK_PATH *__ek_path)
{
    EK_NODE *tmp = __ek_path->root;

    if (tmp == NULL)
    {
        printf("Root: " COLOR_LIGHT_RED "[NULL]" COLOR_RESET "\n");
    }
    else
    {
        while (tmp)
        {
            printf(COLOR_LIGHT_MAGENTA "[%s]" COLOR_RESET, __room_get_room(tmp->id)->name);
            if (tmp->next != NULL)
            {
                printf(COLOR_LIGHT_MAGENTA " -> " COLOR_RESET);
            }
            tmp = tmp->next;
        }
        printf("\n");
    }
}

/*******************************************************************************
 *                                    ANTS                                     *
 ******************************************************************************/

static int __ants_init(void)
{
    if (!(g_ants = malloc(sizeof(ANT) * ANT_COUNT())))
        return (-1);
    for (int i = 0; i < ANT_COUNT(); i++)
    {
        const int x = __room_get_start_room()->x;
        const int y = __room_get_start_room()->y;

        GET_ANT(i).id = i;
        GET_ANT(i).x = x;
        GET_ANT(i).y = y;
        GET_ANT(i).current_room = __room_get_start_room();
    }
    return (0);
}

/*******************************************************************************
 *                                  AI UTILS                                   *
 ******************************************************************************/

static bool __ai_ant_is_in_room(int id)
{
    const int end_room_id = __room_get_end_room()->id;
    for (int i = 0; i < ANT_COUNT(); i++)
    {
        if (GET_ANT(i).current_room->id == id && id != end_room_id)
            return (true);
    }
    return (false);
}

static void __ai_free_ek_nodes(EK_NODE *node)
{
    EK_NODE *tmp = node;

    while (tmp)
    {
        EK_NODE *tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    node = NULL;
}

static int __ai_get_valid_links_length(t_room *valid_links[])
{
    int i = 0;

    for (int j = 0; valid_links[j]; j++)
        i++;
    return (i);
}

static void __ai_get_valid_links(t_room *valid_links[], t_room **links, int size, EK_PATH *__ek_path)
{
    int i = 0, j = 0;
    bool valid = true;

    for (; i < size; i++)
    {
        EK_NODE *tmp = __ek_path->root;

        // Check as been visited
        while (tmp != NULL && tmp->next != NULL)
        {
            if (tmp->flag == true && tmp->id == links[i]->id)
            {
                valid = false;
                break;
            }
            tmp = tmp->next;
        }

        // Check if a ant is on the room
        // const int end_room = __room_get_end_room()->id;
        // for (int k = 0; k < ANT_COUNT(); k++)
        // {
        //     if (GET_ANT(k).current_room->id == links[i]->id && GET_ANT(k).current_room->id != end_room)
        //     {
        //         valid = false;
        //         break;
        //     }
        // }

        if (valid)
        {
            valid_links[j] = links[i];
            j++;
        }
        else
            valid = true;
    }

    valid_links[j] = NULL;

    printf("\tLinks: ");
    for (int k = 0; k < j; k++)
    {
        printf(COLOR_LIGHT_CYAN "[%d]" COLOR_RESET, valid_links[k]->id);
        if (k != j - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}

static EK_NODE *__ek_create_new_node(EK_NODE *root, EK_NODE *prev, int ref_room)
{
    EK_NODE *node = NULL;

    if (!(node = malloc(sizeof(EK_NODE))))
        return (NULL);
    else
    {
        if (prev && ref_room == prev->id)
            return (prev);

        node->next = NULL;
        node->prev = prev == NULL ? NULL : prev;
        node->id = ref_room;
        node->flag = false;
        if (prev != NULL)
            node->depth = prev->depth + 1;
        else
            node->depth = 1;

        if (root == NULL)
        {
            printf("\tNew root: " COLOR_LIGHT_CYAN "[%d]" COLOR_RESET "\n", node->id);
            root = node;
        }
        else
        {
            EK_NODE *tmp = root;

            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = node;
        }
    }
    printf("\t   Create Node " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, node->id);
    printf("\t   Depth: " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, node->depth);
    printf("\t   Flag: " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, node->flag);
    printf("\t   Prev: " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, node->prev == NULL ? -1 : node->prev->id);
    printf("\t   Next: " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, node->next == NULL ? -1 : node->next->id);
    return (node);
}

static int __ek_push_path(EK_PATH *path)
{
    if (!path)
        return (-1);
    else
    {
        EK_PATH **new = NULL;

        const int count = g_ek.path_count;
        if (!(new = (EK_PATH **)malloc(sizeof(EK_PATH) * (count + 2))))
            return (-1);
        for (int i = 0; i < count; i++)
            new[i] = g_ek.path[i];
        new[count] = path;
        new[count + 1] = NULL;
        if (g_ek.path)
            free(g_ek.path);
        g_ek.path = new;
        g_ek.path_count++;
        printf("EK - Push Path\n");
    }
    return (0);
}

/*
** Append path to linked list of ref path
** @param ref: ref path
** @param path: path to append
*/

static int __ek_push_local_path(EK_PATH *ref, EK_PATH *path)
{
    if (!ref || !path)
        return (-1);
    else
    {
        EK_PATH *tmp = ref;

        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = path;
        printf("EK - Push Local Path\n");
    }
    return (0);
}

/*
** GET EK NODE BY ID
** @param id: room id
** @return: EK_NODE *
*/

static EK_NODE *__ek_get_node(EK_PATH *__ek_path, int id)
{
    EK_NODE *tmp = __ek_path->root;

    while (tmp != NULL)
    {
        if (tmp->id == id)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

static EK_PATH *__ek_get_path(int id)
{
    if (id >= PATH_COUNT())
        return (NULL);
    else
    {
        EK_PATH *__ek_path = g_ek.path[id];

        if (!__ek_path)
            return (NULL);

        __ek_path->root = __ek_path->root;
        EK_NODE *node = __ek_get_node(__ek_path, GET_ANT(id).current_room->id);
        if (node)
            __ek_path->current = node->prev;
        if (__ek_path->current == NULL)
            __ek_path->current = __ek_path->root;
        __ek_path->next = NULL; // todo, faire un free

        // if (__ek_path->root && __ek_path->root->next && __ek_path->root->id == __ek_path->root->next->id)
        // {
        //     __ek_path->root = __ek_path->root->next;
        //     __ek_path->root->prev = NULL;
        // }

        printf("- EK GetPath | Root: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", __ek_path->root ? __ek_path->root->id : -1);
        printf("- EK GetPath | Current: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", __ek_path->current ? __ek_path->current->id : -1);

        // __ai_free_ek_nodes(__ek_path->current->next);
        __ek_path->current->next = NULL;
        EK_NODE *tmp = __ek_path->root;

        while (tmp != NULL)
        {
            printf("[%d]", tmp->id);
            if (tmp->next != NULL)
            {
                printf(" -> ");
            }
            tmp = tmp->next;
        }
        printf("\n");

        // pause();

        return (__ek_path);
    }
}

/*
** Copy Path until node
** @param new_path: EK_PATH * -> new_path to copy
** @param ref: EK_PATH * -> ref_path
** @param to_node: EK_NODE * -> copy path to 'to_node'
*/

static EK_PATH *__ek_copy_path(EK_PATH *new_path, EK_PATH *ref, EK_NODE *to_node)
{
    /*
        __new_ek_path->root = __ek_path->root;
        __new_ek_path->current = __ek_path->current;
        __new_ek_path->next = __ek_path->next;
        __new_ek_path->depth = __ek_path->depth + 1;
        __ek_path->next = __new_ek_path;
        __ek_path->next->next = NULL;
    */

    new_path->visited = false;
    new_path->valid = false;
    new_path->depth = ref->depth + 1;
    new_path->blocked = ref->blocked;

    EK_NODE *tmp = ref->root;
    EK_NODE *prev = NULL;

    printf("- Copy Path REF\n");
    __debug_print_root(ref);

    while (tmp != NULL)
    {
        new_path->current = __ek_create_new_node(new_path->root, prev, tmp->id);
        new_path->current->depth = tmp->depth;
        new_path->current->flag = tmp->flag;

        if (new_path->root == NULL)
            new_path->root = new_path->current;
        printf("\t- Add Node " COLOR_LIGHT_CYAN "[%d]\n" COLOR_RESET, tmp->id);
        if (tmp->id == ref->current->id)
            new_path->current = tmp;
        printf("Check [%d] [%d]\n", tmp->id, to_node->id);
        if (tmp->id == to_node->id)
        {
            new_path->current = tmp;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    printf("\tNew path root=%d\n", new_path->root->id);

    printf("- Copy Path\n");
    __debug_print_root(new_path);
    return (new_path);
}

static EK_PATH *__ek_create_path()
{
    EK_PATH *path = NULL;

    if (!(path = malloc(sizeof(EK_PATH))))
        return (NULL);
    path->current = NULL;
    path->root = NULL;
    path->visited = false;
    path->valid = false;
    path->depth = 0;
    path->next = NULL;
    path->blocked = false;
    return (path);
}

/*******************************************************************************
 *                                  AI - ALGO                                  *
 ******************************************************************************/

EK_PATH *__ref_ek_path = NULL; // Ref Path // TMP

static int __ek_find_end_room(EK_PATH *__ek_path, t_room *current_room)
{
    printf(COLOR_LIGHT_CYAN "\n--- PASS [%d.%d] ---\n\n" COLOR_RESET, __ek_path->depth, __ek_path->current != NULL ? __ek_path->current->depth : 0);
    if (!current_room)
    {
        printf(COLOR_LIGHT_YELLOW "Warning: current_room is NULL\n" COLOR_RESET);
        __ek_path->valid = false;
        return (-1);
    }
    if (__ek_path->depth >= __room_get_count())
    {
        printf(COLOR_LIGHT_YELLOW "Warning: __ek_path->depth >= __room_get_count()\n" COLOR_RESET);
        __ek_path->valid = false;
        return (-1);
    }
    printf("AI - Algo: CurrentRoom: " COLOR_GREEN "[%d]" COLOR_RESET "\n", current_room->id);

    EK_NODE *node = NULL;

    node = __ek_create_new_node(__ek_path->root, __ek_path->current, current_room->id);
    if (node == NULL)
    {
        printf(COLOR_LIGHT_YELLOW "Warning: node is NULL\n" COLOR_RESET);
        __ek_path->valid = false;
        return (-1);
    }
    if (__ek_path->root == NULL)
        __ek_path->root = node;
    __ek_path->current = node;
    __ek_path->current->flag = true;

    __debug_print_root(__ek_path);

    if (current_room->id == __room_get_end_room()->id)
    {
        __ek_path->valid = true;
        printf(COLOR_LIGHT_YELLOW "Warning: Last room as been reached\n" COLOR_RESET);
        return (0);
    }

    const int links_count = __room_get_links_count(current_room->id);
    printf("AI - Algo: LinksCount: " COLOR_GREEN " [%d] " COLOR_RESET "\n", links_count);

    t_room *valid_links[links_count + 1];
    __ai_get_valid_links(valid_links, current_room->links, links_count, __ek_path);

    const int valid_links_count = __ai_get_valid_links_length(valid_links);
    printf("\tValidLinksCount: " COLOR_LIGHT_CYAN " [%d] " COLOR_RESET "\n", valid_links_count);

    if (valid_links_count <= 0 && valid_links[0] == NULL)
    {
        printf(COLOR_LIGHT_YELLOW "Warning: No valid links: Ant must WAIT !\n" COLOR_RESET);
        __ek_path->valid = false;
        return (-1);
    }
    else
    {
        for (int i = 0; i < valid_links_count; i++)
        {
            if ((__ai_ant_is_in_room(valid_links[i]->id)) == true)
            {
                printf(COLOR_LIGHT_YELLOW "Warning: Ant is in link: %d\n" COLOR_RESET, valid_links[i]->id);
                __ek_path->valid = false;
                __ek_path->blocked = true;
            }
        }

        if (valid_links_count > 1)
        {
            for (int i = 0; i < valid_links_count; i++)
            {
                if (__ai_ant_is_in_room(valid_links[i]->id) == true)
                    continue;
                printf("AI - Algo: Create New PATH for link: " COLOR_LIGHT_GREEN "[%d - %d]\n" COLOR_RESET, i, valid_links[i]->id);

                EK_PATH *__new_ek_path = __ek_create_path();

                if (!(__new_ek_path))
                {
                    printf(COLOR_RED "Error: __new_ek_path is NULL\n" COLOR_RESET);
                    return (-1);
                }
                else
                {
                    // return (__ek_find_end_room(__new_ek_path, valid_links[i]));

                    __ek_copy_path(__new_ek_path, __ek_path, node);
                    __ek_push_local_path(__ref_ek_path, __new_ek_path);

                    printf("AI - Algo: NextRoom: " COLOR_LIGHT_GREEN "[%d]\n" COLOR_RESET, valid_links[i]->id);
                    //__debug_wait_input();
                    __ek_find_end_room(__new_ek_path, valid_links[i]);
                    printf(COLOR_LIGHT_GREEN "--- END LOOP ---\n" COLOR_RESET);
                    // return (__ek_find_end_room(__new_ek_path, valid_links[i]));
                }
            }
        }
        else
        {
            printf("AI - Algo: NextRoom: " COLOR_LIGHT_GREEN "[%d]\n" COLOR_RESET, valid_links[0]->id);
            // __debug_wait_input();
            return (__ek_find_end_room(__ek_path, valid_links[0]));
        }
        return (0);

        // Le temps de faire les multi branches
        // printf("AI - Algo: NextRoom: " COLOR_LIGHT_GREEN "[%d]\n" COLOR_RESET, valid_links[0]->id);
        // return (__ek_find_end_room(__ek_path, valid_links[0]));
    }
    return (0);
}

static void ai_move_algo(ANT *ant)
{
    printf(COLOR_LIGHT_YELLOW "\n--- ANT [%d] ---\n\n" COLOR_RESET, ant->id);
    t_room *current_room = ant->current_room;

    EK_PATH *__ek_path = NULL;

    if ((__ek_path = __ek_get_path(ant->id)) == NULL)
    {
        printf(COLOR_YELLOW "Warning: " COLOR_RESET "__ek_path is NULL: Create new EK Path\n");
        printf("AI - Algo: Create EK Path\n");
        __ek_path = __ek_create_path();
        __ek_push_path(__ek_path);
    }
    else
        printf("AI - Algo: GET EK Path\n");
    __ref_ek_path = __ek_path;
    __ek_find_end_room(__ek_path, current_room);

    EK_PATH *path = __ek_path;
    int i = 0;
    while (path)
    {
        ++i;
        path = path->next;
    }
    printf("AI - Algo: PathCount: " COLOR_LIGHT_CYAN " [%d] " COLOR_RESET "\n", i);

    /* Get Best Path */
    path = __ek_path;
    EK_PATH *best_path = NULL;
    int best_path_depth = INT_MAX;

    i = 0;
    while (path)
    {
        if (path->valid == true)
        {
            printf("AI - Algo: Path " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " Valid: " COLOR_LIGHT_GREEN "[true]" COLOR_RESET " : Depth: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", i, path->depth);

            if (path->depth < best_path_depth)
            {
                best_path = path;
                best_path_depth = path->depth;
                i++;
            }
            __debug_print_root(best_path);
        }
        path = path->next;
    }

    if (best_path == NULL)
    {
        path = __ek_path;
        while (path)
        {
            if (path->valid == false && path->blocked == true)
            {
                printf("AI - Algo: Path " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " Valid: " COLOR_LIGHT_GREEN "[false]" COLOR_RESET " : Depth: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", i, path->depth);
                best_path = path;
                best_path_depth = path->depth;
                i++;
            }
            path = path->next;
        }
    }

    printf("BestPAth: " COLOR_LIGHT_CYAN " [%d] [%d] " COLOR_RESET "\n", i, best_path ? best_path->depth : -1);
    __ek_path = best_path;

    EK_NODE *tmp = NULL;
    if (__ek_path)
    {
        tmp = __ek_path->root;
        while (tmp)
        {
            if (tmp->id == ant->current_room->id)
                break;
            tmp = tmp->next;
        }
    }

    // if (__ek_path->root && __ek_path->root->next)
    if (tmp && tmp->next)
    {
        printf("AI - Algo: EK Path: " COLOR_GREEN "[%d] " COLOR_RESET "\n", tmp->next->id);
        const int room_id = tmp->next->id;
        const char *room_name = __room_get_room(room_id)->name;
        ant->current_room = __room_get_room(room_id);
        ant->x = __room_get_room(room_id)->x;
        ant->y = __room_get_room(room_id)->y;
        printf("L%d-%s ", ant->id + 1, room_name);
    }
    else
    {
        printf(COLOR_YELLOW "Warning:" COLOR_RESET " No path found\n");
    }

    if (__ek_path)
    {

        tmp = __ek_path->root;

        while (tmp)
        {
            if (ant->current_room->id == tmp->id)
                printf(COLOR_LIGHT_GREEN);
            printf("[%s]" COLOR_RESET, __room_get_room(tmp->id)->name);
            if (tmp->id == __room_get_end_room()->id)
                break;
            if (tmp->next != NULL)
            {
                printf(" -> ");
            }
            tmp = tmp->next;
        }
    }
    // exit(0);
    printf("\n");
}

static bool check_end(void)
{
    const int end_room = __room_get_end_room()->id;

    for (int i = 0; i < ANT_COUNT(); i++)
    {
        if (g_ants[i].current_room->id != end_room)
            return (false);
    }
    return (true);
}

static void delete_ant(ANT *ant)
{
    // TODO, check
    const int room_id = ant->current_room->id;
    const int end_room_id = __room_get_end_room()->id;

    if (room_id == end_room_id)
    {
        printf(COLOR_LIGHT_GREEN "Ant [%d] - " COLOR_RESET "End Room\n", ant->id);
        ant->current_room = NULL;
        ant->x = 0;
        ant->y = 0;
    }
    else
        return;
}

static void __ai_clean_ek(void)
{
    // FREE ANTS
    printf("Free Ant: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", ANT_COUNT());
    free(g_ants);

    // FREE EK PATH & NODES
    for (int i = 0; i < PATH_COUNT(); i++)
    {
        EK_PATH *path = g_ek.path[i];

        if (path)
        {
            EK_NODE *node = path->root;
            while (node)
            {
                EK_NODE *tmp = node;
                node = node->next;
                if (tmp)
                    free(tmp);
            }

            free(path);
            path = NULL;
        }
        printf("Free Path: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET "\n", i);
    }
}

int ai_main(void)
{
    printf(COLOR_LIGHT_GREEN "\n##### AI MAIN #####\n\n" COLOR_RESET);

    /* INIT ANTS */
    if ((__ants_init()) == -1)
        return (-1);

    // __room_count = get_room_count();

    int turn = 0;
    for (; check_end() == false; turn++)
    {
        printf(COLOR_LIGHT_RED "\n--- TOUR [%d] ---\n" COLOR_RESET, turn);
        for (int j = 0; j < ANT_COUNT(); j++)
        {
            ANT *ant = &g_ants[j];
            if (ant->current_room->id == __room_get_end_room()->id)
                continue;
            clock_t start = clock();
            ai_move_algo(ant);
            clock_t end = clock();
            // __debug_wait_input();

            printf("Elapsed: " COLOR_LIGHT_GREEN "[%d]" COLOR_RESET " ms\n", (int)(end - start));
            printf("Elapsed: " COLOR_LIGHT_GREEN "[%f]" COLOR_RESET " seconds\n", (float)((end - start) / CLOCKS_PER_SEC));
            // pause();

            printf("\n"); // TMP a retirer
            printf("Update Ant Room: " COLOR_GREEN "[%d]" COLOR_RESET "\n", ant->current_room->id);
            // delete_ant(ant);
            //__debug_wait_input();
            pause();
        }
    // pause();
        printf("\n");

        for (int j = 0; j < ANT_COUNT(); j++)
        {
            printf(COLOR_LIGHT_YELLOW "- Ant [%d] - Room: [%s]\n" COLOR_RESET, j, g_ants[j].current_room->name);
        }
    }
    printf(COLOR_LIGHT_GREEN "--- END in [%d] tours ---\n" COLOR_RESET, turn);
    __ai_clean_ek();
    return (0);
}

/*
TODO ALGO:

- Récupérer les anciens ek path faits par les fourmis. pour pas qu'elles reviennent en arrière
- Créer un nouveau path pour chaque nouveau lien (cf. text_map01 - room 7)

- peut être, a la place de modifier l'algo récupérer, laisser comme ça et ajuster avec le nouvel emplacement de la fourmi
*/

/*
la derniere fourmis avance en derniere quand les autres sont arrivées a la fin car la condition si link[i], vérifie s'il y a une fourmi, si c'est le cas, la branche est mise à false
-> todo, laisser la branche passer même s'il y a une fourmi et checker s'il y a une fourmi à la fin

-> todo, sujet example, fourmis qui se bloquent

si un graph parcouru n'a aucun element valide (path valid) -> alors récupérer ...
-> mettre un bool blocked by ant pour que si une fourmis n'a aucun graph valide, elle parse ceux qui sont bloqués par les fourmis ensuite, checker si elle peut y aller
*/

/*
    IA ALGO:

    Creer un arbre pour chaque fourmis
    -	crer un arbre:
        - 	pour chaque links du debut creer une branch
            -	parcourir la prochaine salle et continuer la branche
                -	si la salle contient plusieurs chemins, crer une branche pour chaque chemin
            -	Continuer tant qu'il y a une salle enfant
            -	Ne jamais prendre la salle parent, comme ca, il ne pourra jamais y avoir de boucles / cycles infinis.
            -	Si une branche arrive a un child NULL -> la delete
            -	si une branche arrive a la salle de fin, on la recupere pour le path a faire
            -	attendre que toute les branches soient finies pour recuperer la meilleure branche

    -	Ajouter par la suite:
        -	blocage des chemins par d autres fourmis
        - 	Possibilite d'attendre pour un meilleur chemin

*/

/*
    TODO:

    Voir avec matthieu pour faire un tableau de links. (struct s_room **links) et pas un seul *
*/

/*
    IA Algo Début:

    Avancer dans la map vers le point final.
    - Si a un moment on croise un point déjà existant, revenir au dernier emplacement avec plusieurs links

*/