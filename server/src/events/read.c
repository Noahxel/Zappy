/*
** EPITECH PROJECT, 2023
** read.c
** File description:
** read
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "network.h"
#include "tools.h"

static void read_client(client_t * const client, bool * const is_there_gui)
{
    int bytes_read = 0;

    CERROR((bytes_read = read(client->fd, client->read_buf,
    BUFFER_SIZE - 1)) == FAIL, "read");
    if (bytes_read == 0) {
        client->status == GUI ? *is_there_gui = false : 0;
        client->status = INVALID;
        return;
    }
    client->read_buf[bytes_read] = '\0';
    client->commands = my_str_to_array(client->read_buf, "\n");
    if (client->commands)
        for (int i = 0; client->commands[i]; i++)
            printf("RECEIVE: %s\n", client->commands[i]);
}

void handle_read_event(network_t * const network)
{
    for (client_t *tmp = network->client; tmp; tmp = tmp->next)
        if (FD_ISSET(tmp->fd, &network->readfds))
            read_client(tmp, &network->is_there_gui);
}
