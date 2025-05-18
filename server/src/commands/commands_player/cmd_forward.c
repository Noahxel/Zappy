/*
** EPITECH PROJECT, 2023
** player_forward.c
** File description:
** player_forward
*/

#include <stdio.h>
#include <string.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_forward(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    client->player->orientation == N ? client->player->coordinate.y == 0 ?
    client->player->coordinate.y = game->map->height - 1 :
    client->player->coordinate.y-- : client->player->orientation == E ?
    client->player->coordinate.x == game->map->width - 1 ?
    client->player->coordinate.x = 0 : client->player->coordinate.x++ :
    client->player->orientation == S ? client->player->coordinate.y ==
    game->map->height - 1 ? client->player->coordinate.y = 0 :
    client->player->coordinate.y++ : client->player->orientation == W ?
    client->player->coordinate.x == 0 ? client->player->coordinate.x =
    game->map->width - 1 : client->player->coordinate.x-- : 0;
    sprintf(buffer, PPO_PATTERN, client->player->id,
    client->player->coordinate.x, client->player->coordinate.y,
    client->player->orientation);
    add_response(get_gui(head), buffer);
    add_response(client, M_OK);
}
