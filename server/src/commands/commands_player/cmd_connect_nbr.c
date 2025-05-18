/*
** EPITECH PROJECT, 2023
** player_connect_nbr.c
** File description:
** player_connect_nbr
*/

#include <stdio.h>
#include <string.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_connect_nbr(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    team_t *tmp;

    for (tmp = game->team; tmp; tmp = tmp->next)
        if (!strcmp(tmp->team_name, client->player->team->team_name))
            break;
    sprintf(buffer, "%d\n",tmp->available_slots);
    add_response(client, buffer);
}
