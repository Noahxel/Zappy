/*
** EPITECH PROJECT, 2023
** socket.c
** File description:
** socket
*/

#include "network.h"

void reset_socket_fd(network_t * const network)
{
    FD_ZERO(&network->readfds);
    FD_ZERO(&network->writefds);
    FD_SET(network->sock.fd, &network->readfds);
    FD_SET(network->sock.fd, &network->writefds);
    network->max_fd = network->sock.fd;
    for (client_t *tmp = network->client; tmp; tmp = tmp->next)
        if (tmp->fd) {
            FD_SET(tmp->fd, &network->readfds);
            FD_SET(tmp->fd, &network->writefds);
            tmp->fd > network->max_fd ? network->max_fd = tmp->fd : 0;
        }
}
