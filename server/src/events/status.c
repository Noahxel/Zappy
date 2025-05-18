/*
** EPITECH PROJECT, 2023
** status.c
** File description:
** status
*/

#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static void invalid_or_dead(network_t * const network,
client_t * const tmp, game_t * const game)
{
    char buffer[BUFFER_SIZE];

    if (tmp->status != GUI && (tmp->status == INVALID ||
    (tmp->player && tmp->player->status == DEAD))) {
        if (tmp->player) {
            create_player(&game->player, tmp->player->team,
            game->map, 0);
            tmp->player->team->available_slots++;
            sprintf(buffer, PDI_PATTERN, tmp->player->id);
            add_response(get_gui(network->client), buffer);
            remove_player(&game->player, tmp->player);
        }
        disconnect_client(&network->client, tmp);
    }
}

void handle_status_event(network_t * const network, game_t * const game)
{
    for (client_t *tmp = network->client, *next_tmp; tmp; tmp = next_tmp) {
        next_tmp = tmp->next;
        invalid_or_dead(network, tmp, game);
    }
}
