/*
** EPITECH PROJECT, 2023
** clients.c
** File description:
** clients
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "tools.h"

client_t *get_gui(client_t * const head)
{
    for (client_t *tmp = head; tmp; tmp = tmp->next)
        if (tmp->status == GUI)
            return tmp;
    return NULL;
}

void disconnect_client(client_t ** const head, client_t * const client)
{
    client_t *prev = NULL;

    for (client_t *tmp = *head; tmp; prev = tmp, tmp = tmp->next) {
        if (tmp != client)
            continue;
        !prev ? (*head = tmp->next) : (prev->next = tmp->next);
        M_DISCONNECTION(client->fd);
        my_free_array(client->commands);
        my_free_array(client->write_buf);
        free_queue(&client->queue);
        close(client->fd);
        free(tmp);
        return;
    }
}

static client_t *set_data_new_client(const int new_fd)
{
    client_t *new_client = malloc(sizeof(client_t));
    CERROR(new_client == NULL, "malloc");

    new_client->fd = new_fd;
    new_client->queue.size = 0;
    new_client->queue.head = 0;
    new_client->queue.tail = 0;
    new_client->queue.head = NULL;
    new_client->queue.tail = NULL;
    new_client->status = NONE;
    new_client->commands = NULL;
    new_client->player = NULL;
    new_client->write_buf = NULL;
    new_client->next = NULL;
    return new_client;
}

static client_t *add_new_client_to_others(client_t * const head,
client_t * const new_client)
{
    client_t *tmp;
    new_client->next = NULL;

    if (head == NULL)
        return new_client;
    for (tmp = head; tmp->next; tmp = tmp->next);
    tmp->next = new_client;
    return head;
}

void create_client(client_t ** const head, const int new_fd)
{
    client_t *new_client = set_data_new_client(new_fd);
    *head = add_new_client_to_others(*head, new_client);
    M_WELCOME(new_fd);
}
