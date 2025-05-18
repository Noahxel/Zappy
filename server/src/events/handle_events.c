/*
** EPITECH PROJECT, 2023
** handle_events.c
** File description:
** handle_events
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "network.h"
#include "event.h"
#include "game.h"

void handle_events(game_t * const game, network_t * const network)
{
    handle_new_connection_event(network);
    handle_end_game(network->client, game);
    handle_time_event(network->client, game);
    handle_read_event(network);
    handle_assignment(network, game);
    handle_command(network);
    handle_execution(network, game);
    handle_write_event(network);
    handle_status_event(network, game);
}
