/*
** EPITECH PROJECT, 2023
** assignment.c
** File description:
** assignment
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static void set_assignment(network_t * const network,
client_t * const client, game_t * const game)
{
    if (!strcmp(client->commands[0], "GRAPHIC")) {
        assignment_to_gui(client, &network->is_there_gui);
    } else
        assignment_to_team(get_gui(network->client), client, game);
    free(client->commands[0]);
    for (int i = 0; client->commands[i]; i++)
        client->commands[i] = client->commands[i + 1];
}

void handle_assignment(network_t * const network, game_t * const game)
{
    for (client_t *tmp = network->client; tmp; tmp = tmp->next)
        if (tmp->status == NONE && tmp->commands)
            set_assignment(network, tmp, game);
}
