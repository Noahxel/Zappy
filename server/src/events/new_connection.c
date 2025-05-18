/*
** EPITECH PROJECT, 2023
** new_connection.c
** File description:
** new_connection
*/

#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "network.h"

void handle_new_connection_event(network_t * const network)
{
    if (FD_ISSET(network->sock.fd, &network->readfds)) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int new_fd = accept(network->sock.fd, (struct sockaddr *)&addr, &len);
        CERROR(new_fd == FAIL, "accept");
        M_CONNECTION(new_fd);
        create_client(&network->client, new_fd);
    }
}
