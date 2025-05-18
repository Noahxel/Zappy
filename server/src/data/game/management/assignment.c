/*
** EPITECH PROJECT, 2023
** assignment.c
** File description:
** assignment
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static void link_player_to_team(client_t * const client,
player_t * const player, int * const given_id)
{
    player->id = ++(*given_id);
    client->status = PLAYER;
    client->player = player;
    client->player->team->available_slots--;
    client->player->inventory.food--;
    clock_gettime(1, &client->player->time_info.last_eat_cooldown);
    client->player->status = ALIVE;
}

static player_t *assign_team_status(client_t * const client,
game_t * const game, client_t * const gui)
{
    char buffer[BUFFER_SIZE];

    for (player_t *tmp = game->player; tmp; tmp = tmp->next)
        if (!strcmp(client->commands[0], tmp->team->team_name)
        && (tmp->status == UNAFFECTED || tmp->status == EGG)
        && tmp->team->available_slots > 0) {
            sprintf(buffer, EBO_PATTERN, tmp->id);
            tmp->status == EGG ? sprintf(buffer, EBO_PATTERN, tmp->id),
            add_response(gui, buffer),
            sprintf(buffer, EDI_PATTERN, tmp->id),
            add_response(gui, buffer) : 0;
            link_player_to_team(client, tmp, &game->given_id);
            return tmp;
        }
    return NULL;
}

void assignment_to_team(client_t * const gui,
client_t * const client, game_t * const game)
{
    char buffer[BUFFER_SIZE];
    player_t *assigned_player = assign_team_status(client, game, gui);

    if (assigned_player) {
        sprintf(buffer, "%d\n", assigned_player->team->available_slots);
        add_response(client, buffer);
        sprintf(buffer, "%d %d\n", game->map->width, game->map->height);
        add_response(client, buffer);
        sprintf(buffer, PNW_PATTERN, assigned_player->id,
        assigned_player->coordinate.x, assigned_player->coordinate.y,
        assigned_player->orientation, assigned_player->level,
        assigned_player->team->team_name);
        return add_response(gui, buffer);
    }
    add_response(client, M_KO);
    client->status = INVALID;
}

void assignment_to_gui(client_t * const client, bool * const is_there_gui)
{
    if (*is_there_gui == true) {
        client->status = INVALID;
        my_free_array(client->write_buf);
        return add_response(client, M_KO);
    }
    client->status = GUI;
    *is_there_gui = true;
}
