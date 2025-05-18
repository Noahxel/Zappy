/*
** EPITECH PROJECT, 2023
** player_left.c
** File description:
** player_left
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_left(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    client->player->orientation == N ? client->player->orientation = W :
    client->player->orientation == W ? client->player->orientation = S :
    client->player->orientation == S ? client->player->orientation = E :
    client->player->orientation == E ? client->player->orientation = N : 0;
    sprintf(buffer, PPO_PATTERN, client->player->id,
    client->player->coordinate.x, client->player->coordinate.y,
    client->player->orientation);
    add_response(get_gui(head), buffer);
    add_response(client, M_OK);
}
