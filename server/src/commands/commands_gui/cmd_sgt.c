/*
** EPITECH PROJECT, 2023
** cmd_sgt.c
** File description:
** cmd_sgt
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_sgt(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    sprintf(buffer, SGT_PATTERN, game->freq);
    add_response(client, buffer);
}
