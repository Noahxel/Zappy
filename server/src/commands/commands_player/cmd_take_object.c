/*
** EPITECH PROJECT, 2023
** player_take_object.c
** File description:
** player_take_object
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static int is_take_valid(resource_t * const resource,
resource_t * const inventory, const char * const object)
{
    if (!object)
        return R_NONE;
    return !strcmp(object, "food") && resource->food > 0 ?
    (--resource->food, ++inventory->food, R_FOOD) :
    !strcmp(object, "linemate") && resource->linemate > 0 ?
    (--resource->linemate, ++inventory->linemate, R_LINEMATE) :
    !strcmp(object, "deraumere") && resource->deraumere > 0 ?
    (--resource->deraumere, ++inventory->deraumere, R_DERAUMERE) :
    !strcmp(object, "sibur") && resource->sibur > 0 ?
    (--resource->sibur, ++inventory->sibur, R_SIBUR) :
    !strcmp(object, "mendiane") && resource->mendiane > 0 ?
    (--resource->mendiane, ++inventory->mendiane, R_MENDIANE) :
    !strcmp(object, "phiras") && resource->phiras > 0 ?
    (--resource->phiras, ++inventory->phiras, R_PHIRAS) :
    !strcmp(object, "thystame") && resource->thystame > 0 ?
    (--resource->thystame, ++inventory->thystame, R_THYSTAME) :
    R_NONE;
}

void cmd_take_object(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    resource_type_e resource_type;
    resource_t *inventory = &(client->player->inventory);
    resource_t *resource = &(game->map->tile
    [client->player->coordinate.x][client->player->coordinate.y]);

    if ((resource_type = is_take_valid(resource, inventory,
    client->queue.head->command.arg)) != R_NONE) {
        sprintf(buffer, PGT_PATTERN, client->player->id, resource_type);
        add_response(get_gui(head), buffer);
        sprintf(buffer, BCT_PATTERN, client->player->coordinate.x,
        client->player->coordinate.y, resource->food, resource->linemate,
        resource->deraumere, resource->sibur, resource->mendiane,
        resource->phiras, resource->thystame);
        add_response(get_gui(head), buffer);
        add_response(client, M_OK);
        return;
    }
    add_response(client, M_KO);
}
