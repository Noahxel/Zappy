/*
** EPITECH PROJECT, 2023
** player_inventory.c
** File description:
** player_inventory
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void cmd_inventory(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    sprintf(buffer, INVENTORY_PATTERN,
    client->player->inventory.food * FOOD_TIME_LIMIT,
    client->player->inventory.linemate, client->player->inventory.deraumere,
    client->player->inventory.sibur, client->player->inventory.mendiane,
    client->player->inventory.phiras, client->player->inventory.thystame);
    add_response(client, buffer);
}
