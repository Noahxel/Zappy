/*
** EPITECH PROJECT, 2023
** network.c
** File description:
** network
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "network.h"
#include "tools.h"
#include "init.h"

void init_network(const char * const *av, network_t * const network)
{
    network->is_there_gui = false;
    network->client = NULL;
    init_server_socket(&network->sock, get_flag(av, "-p"));
    CERROR(listen(network->sock.fd, SOMAXCONN) == FAIL, "listen");
}
