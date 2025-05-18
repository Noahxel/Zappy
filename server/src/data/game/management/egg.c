/*
** EPITECH PROJECT, 2023
** egg.c
** File description:
** egg
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "management.h"
#include "tools.h"
#include "game.h"

static player_t *set_data_new_egg(team_t * const team,
const map_t * const map, const int id)
{
    player_t *new_egg = malloc(sizeof(player_t));
    CERROR(new_egg == NULL, "malloc");

    new_egg->id = id;
    init_time_info(&new_egg->time_info);
    new_egg->orientation = rand() % LEN_ORIENTATION + 1;
    new_egg->team = team;
    new_egg->inventory = create_inventory();
    new_egg->coordinate = give_map_coordinate(map->width, map->height);
    new_egg->status = EGG;
    new_egg->level = 1;
    new_egg->next = NULL;
    return new_egg;
}

static player_t *add_new_egg_to_others(player_t * const head,
player_t * const new_egg)
{
    player_t *tmp;
    new_egg->next = NULL;

    if (head == NULL)
        return new_egg;
    for (tmp = head; tmp->next; tmp = tmp->next);
    tmp->next = new_egg;
    return head;
}

void create_egg(player_t ** const head, team_t * const team,
const map_t * const map, const int id)
{
    player_t *new_egg = set_data_new_egg(team, map, id);
    *head = add_new_egg_to_others(*head, new_egg);
}
