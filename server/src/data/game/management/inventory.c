/*
** EPITECH PROJECT, 2023
** inventory.c
** File description:
** inventory
*/

#include "game.h"

resource_t create_inventory(void)
{
    resource_t inventory;

    inventory.food = 10;
    inventory.linemate = 0;
    inventory.deraumere = 0;
    inventory.sibur = 0;
    inventory.mendiane = 0;
    inventory.phiras = 0;
    inventory.thystame = 0;
    return inventory;
}
