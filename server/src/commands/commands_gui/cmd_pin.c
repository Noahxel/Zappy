/*
** EPITECH PROJECT, 2023
** cmd_msz.c
** File description:
** cmd_pin
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_pin(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    int player_id;
    player_t *tmp;

    sscanf(client->queue.head->command.arg, "pin #%d", &player_id);
    for (tmp = game->player; tmp; tmp = tmp->next)
        if (tmp->id == player_id)
            break;
    sprintf(buffer, PIN_PATTERN, tmp->id, tmp->coordinate.x, tmp->coordinate.y,
    tmp->inventory.food, tmp->inventory.linemate, tmp->inventory.deraumere,
    tmp->inventory.sibur, tmp->inventory.mendiane, tmp->inventory.phiras,
    tmp->inventory.thystame);
    add_response(client, buffer);
}
