/*
** EPITECH PROJECT, 2023
** cmd_pwa.c
** File description:
** cmd_pwa
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_pwa(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    for (player_t *tmp = game->player; tmp; tmp = tmp->next) {
        tmp->status != UNAFFECTED ? sprintf(buffer, PNW_PATTERN,
        tmp->id, tmp->coordinate.x, tmp->coordinate.y, tmp->orientation,
        tmp->level, tmp->team->team_name), add_response(client, buffer) : 0;
    }
}
