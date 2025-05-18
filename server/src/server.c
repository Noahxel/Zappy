/*
** EPITECH PROJECT, 2023
** server.c
** File description:
** server
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "management.h"
#include "network.h"
#include "destroy.h"
#include "server.h"
#include "event.h"
#include "game.h"
#include "init.h"

static int server_loop(game_t * const game, network_t * const network)
{
    struct timeval timeout = {TIMEOUT_TIME, 0};
    int select_val;

    reset_socket_fd(network);
    CERROR((select_val = select(network->max_fd + 1, &network->readfds,
    &network->writefds, NULL, &timeout)) == FAIL, "select");
    return select_val == 0 ? M_SERVER_CLOSE : HANDLE_EVENTS;
}

static void init_server(const char * const * const av,
game_t *game, network_t *network)
{
    srand(time(NULL));
    init_game(av, game);
    init_network(av, network);
}

int server(const char * const * const av)
{
    game_t game = {0};
    network_t network = {0};

    init_server(av, &game, &network);
    M_SERVER_START(network.sock.fd);
    while (server_loop(&game, &network));
    destroy_game(game);
    return SUCCESS;
}
