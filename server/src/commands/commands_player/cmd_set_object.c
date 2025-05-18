/*
** EPITECH PROJECT, 2023
** player_set_object.c
** File description:
** player_set_object
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static int is_set_valid
(resource_t *resource, resource_t *inventory, char *object)
{
    if (!object)
        return R_NONE;
    return !strcmp(object, "food") && inventory->food > 0 ?
    (--inventory->food, ++resource->food, R_FOOD) :
    !strcmp(object, "linemate") && inventory->linemate > 0 ?
    (--inventory->linemate, ++resource->linemate, R_LINEMATE) :
    !strcmp(object, "deraumere") && inventory->deraumere > 0 ?
    (--inventory->deraumere, ++resource->deraumere, R_DERAUMERE) :
    !strcmp(object, "sibur") && inventory->sibur > 0 ?
    (--inventory->sibur, ++resource->sibur, R_SIBUR) :
    !strcmp(object, "mendiane") && inventory->mendiane > 0 ?
    (--inventory->mendiane, ++resource->mendiane, R_MENDIANE) :
    !strcmp(object, "phiras") && inventory->phiras > 0 ?
    (--inventory->phiras, ++resource->phiras, R_PHIRAS) :
    !strcmp(object, "thystame") && inventory->thystame > 0 ?
    (--inventory->thystame, ++resource->thystame, R_THYSTAME) :
    R_NONE;
}

void cmd_set_object(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    resource_type_e resource_type;
    resource_t *inventory = &(client->player->inventory);
    resource_t *resource = &(game->map->tile
    [client->player->coordinate.x][client->player->coordinate.y]);

    if ((resource_type = is_set_valid(resource, inventory,
    client->queue.head->command.arg)) != R_NONE) {
        sprintf(buffer, PDR_PATTERN, client->player->id, resource_type);
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
