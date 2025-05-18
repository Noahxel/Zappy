/*
** EPITECH PROJECT, 2023
** cmd_msz.c
** File description:
** cmd_msz
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_msz(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    sprintf(buffer, MSZ_PATTERN, game->map->width, game->map->height);
    add_response(client, buffer);
}
