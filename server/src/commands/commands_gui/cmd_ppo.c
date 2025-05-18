/*
** EPITECH PROJECT, 2023
** cmd_ppo.c
** File description:
** cmd_ppo
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_ppo(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    int player_id;
    player_t *tmp;

    sscanf(client->queue.head->command.arg, "ppo #%d", &player_id);
    for (tmp = game->player; tmp; tmp = tmp->next)
        if (tmp->id == player_id)
            break;
    sprintf(buffer, PPO_PATTERN, tmp->id,
    tmp->coordinate.x, tmp->coordinate.y, tmp->orientation);
    add_response(client, buffer);
}
