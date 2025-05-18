/*
** EPITECH PROJECT, 2023
** cmd_mct.c
** File description:
** cmd_mct
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_mct(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    resource_t resource;

    for (int i = 0; i < game->map->height; i++)
        for (int j = 0; j < game->map->width; j++) {
            resource = game->map->tile[j][i];
            sprintf(buffer, BCT_PATTERN, j, i, resource.food,
            resource.linemate, resource.deraumere, resource.sibur,
            resource.mendiane, resource.phiras, resource.thystame);
            add_response(client, buffer);
        }
}
