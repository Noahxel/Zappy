/*
** EPITECH PROJECT, 2023
** cmd_plv.c
** File description:
** cmd_plv
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_plv(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    int player_id;
    player_t *tmp;

    sscanf(client->queue.head->command.arg, "plv #%d", &player_id);
    for (tmp = game->player; tmp; tmp = tmp->next)
        if (tmp->id == player_id)
            break;
    sprintf(buffer, PLV_PATTERN, tmp->id, tmp->level);
    add_response(client, buffer);
}
