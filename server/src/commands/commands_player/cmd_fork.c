/*
** EPITECH PROJECT, 2023
** player_fork.c
** File description:
** player_fork
*/

#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void fork_by_player(client_t * const head,
client_t * const client, game_t * const game)
{
    char buffer[BUFFER_SIZE];
    player_t *tmp = NULL;
    int egg_x = 0;
    int egg_y = 0;

    create_egg(&game->player, client->player->team,
    game->map, ++game->given_id);
    client->player->team->available_slots++;
    for (tmp = game->player; tmp; tmp = tmp->next)
        if (tmp->status == EGG) {
            egg_x = tmp->coordinate.x;
            egg_y = tmp->coordinate.y;
        }
    sprintf(buffer, ENW_PATTERN, game->given_id,
    client->player->id, egg_x, egg_y);
    add_response(client, M_OK);
    add_response(get_gui(head), buffer);
}

void cmd_fork(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    clock_gettime(1, &client->player->time_info.fork_start_time);
    client->player->status = FORKING;
}
