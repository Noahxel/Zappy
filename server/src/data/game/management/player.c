/*
** EPITECH PROJECT, 2023
** player.c
** File description:
** player
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "management.h"
#include "tools.h"
#include "game.h"

void remove_player(player_t ** const head, const player_t * const player)
{
    player_t *prev_player = NULL;

    for (player_t *tmp = *head; tmp; prev_player = tmp, tmp = tmp->next) {
        if (tmp != player)
            continue;
        prev_player ? (prev_player->next = tmp->next) : (*head = tmp->next);
        free(tmp);
        return;
    }
}

static player_t *set_data_new_player(team_t * const team,
const map_t * const map, const int id)
{
    player_t *new_player = malloc(sizeof(player_t));
    CERROR(new_player == NULL, "malloc");

    new_player->id = id;
    init_time_info(&new_player->time_info);
    new_player->orientation = rand() % LEN_ORIENTATION + 1;
    new_player->team = team;
    new_player->inventory = create_inventory();
    new_player->coordinate = give_map_coordinate(map->width, map->height);
    new_player->status = UNAFFECTED;
    new_player->level = 1;
    new_player->next = NULL;
    return new_player;
}

static player_t *add_new_player_to_others(player_t * const head,
player_t * const new_player)
{
    player_t *tmp;
    new_player->next = NULL;

    if (head == NULL)
        return new_player;
    for (tmp = head; tmp->next; tmp = tmp->next);
    tmp->next = new_player;
    return head;
}

void create_player(player_t ** const head, team_t * const team,
const map_t * const map, const int id)
{
    player_t *new_player = set_data_new_player(team, map, id);
    *head = add_new_player_to_others(*head, new_player);
}
