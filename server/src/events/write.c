/*
** EPITECH PROJECT, 2023
** write.c
** File description:
** write
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "management.h"
#include "my_time.h"
#include "network.h"
#include "tools.h"
#include "game.h"

static void write_message(client_t * const client)
{
    for (int i = 0; client->write_buf[i]; i++) {
        printf("SENDING: %s", client->write_buf[i]);
        ssize_t sent = send(client->fd, client->write_buf[i],
        strlen(client->write_buf[i]), 0);
        CERROR(sent == FAIL, "send");
    }
    my_free_array(client->write_buf);
    client->write_buf = NULL;
}

void handle_write_event(const network_t * const network)
{
    for (client_t *tmp = network->client; tmp; tmp = tmp->next) {
        if (!tmp->write_buf || !tmp->write_buf[0])
            continue;
        if (FD_ISSET(tmp->fd, &network->writefds) && tmp->write_buf) {
            tmp->status == GUI ? write_message(tmp) : 0;
            tmp->status == PLAYER ? write_message(tmp) : 0;
        }
    }
}
