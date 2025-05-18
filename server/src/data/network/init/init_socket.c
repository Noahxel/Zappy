/*
** EPITECH PROJECT, 2023
** init_socket.c
** File description:
** init_socket
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "network.h"
#include "tools.h"

void init_server_socket(socket_t * const sock, const int port)
{
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    CERROR(sock->fd == FAIL, "socket");
    sock->len = sizeof(struct sockaddr_in);
    memset(&sock->addr, 0, sock->len);
    sock->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->addr.sin_port = htons(port);
    CERROR(bind(sock->fd, (const struct sockaddr *)
    &sock->addr, sock->len) == FAIL, "bind");
}
