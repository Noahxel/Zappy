/*
** EPITECH PROJECT, 2023
** cmd_bct.c
** File description:
** cmd_bct
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_bct(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    int x = 0;
    int y = 0;
    char buffer[BUFFER_SIZE];
    sscanf(client->queue.head->command.arg, "bct %d %d", &x, &y);
    resource_t resource = game->map->tile[x][y];

    sprintf(buffer, BCT_PATTERN, x, y, resource.food,
    resource.linemate, resource.deraumere, resource.sibur,
    resource.mendiane, resource.phiras, resource.thystame);
    add_response(client, buffer);
}
