/*
** EPITECH PROJECT, 2023
** network.h
** File description:
** network
*/

#pragma once

#include <netinet/in.h>
#include <sys/select.h>
#include <stdbool.h>

#include "command.h"

typedef struct player_s player_t;

#define M_CONNECTION(fd) printf(CONNECTION_MESS, fd);

static const char CONNECTION_MESS[] = "Connection with fd [%d].\n";

typedef enum {
    GUI,
    PLAYER,
    INVALID,
    NONE
} client_status_e;

typedef struct socket_s {
    int fd;
    socklen_t len;
    struct sockaddr_in addr;
} socket_t;

typedef struct client_s {
    int fd;
    char **commands;
    char read_buf[1024];
    char **write_buf;
    struct sockaddr_in addr;
    player_t *player;
    queue_t queue;
    client_status_e status;
    struct client_s *next;
} client_t;

typedef struct network_s {
    socket_t sock;
    fd_set readfds;
    fd_set writefds;
    int max_fd;
    client_t *client;
    bool is_there_gui;
} network_t;
