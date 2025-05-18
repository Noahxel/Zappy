/*
** EPITECH PROJECT, 2023
** cmd_tna.c
** File description:
** cmd_tna
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_tna(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    for (team_t *tmp = game->team; tmp; tmp = tmp->next) {
        sprintf(buffer, TNA_PATTERN, tmp->team_name);
        add_response(client, buffer);
    }
}
