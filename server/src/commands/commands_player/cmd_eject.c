/*
** EPITECH PROJECT, 2023
** player_eject.c
** File description:
** player_eject
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static orientation_e eject(player_t *ejected_player,
orientation_e push_orientation, map_t *map)
{
    push_orientation == N ? ejected_player->coordinate.y-- :
    push_orientation == S ? ejected_player->coordinate.y++ :
    push_orientation == E ? ejected_player->coordinate.x++ :
    push_orientation == W ? ejected_player->coordinate.x-- : 0;
    ejected_player->coordinate.y < 0 ?
    ejected_player->coordinate.y = map->height - 1 :
    ejected_player->coordinate.y > map->height ?
    ejected_player->coordinate.y = 0 : ejected_player->coordinate.x < 0 ?
    ejected_player->coordinate.x = map->width - 1 :
    ejected_player->coordinate.x > map->width ?
    ejected_player->coordinate.x = 0 : 0;

    return push_orientation == N ? S : push_orientation == S ? N :
    push_orientation == E ? W : push_orientation == W ? E : 0;
}

static bool is_valid_player(client_t * const head,
client_t * const client, game_t * const game, client_t * const tmp)
{
    char buffer[BUFFER_SIZE];

    if (tmp->player->id != client->player->id && tmp->status != GUI
        && IS_SAME_COORD(client->player->coordinate, tmp->player->coordinate)
        && tmp->player->status == EGG) {
            sprintf(buffer, EDI_PATTERN, tmp->player->id);
            add_response(get_gui(head), buffer);
            remove_player(&game->player, tmp->player);
            tmp->status = INVALID;
            return false;
        }
    if (tmp->player->id != client->player->id && tmp->status != GUI
        && IS_SAME_COORD(client->player->coordinate, tmp->player->coordinate))
        return true;
    return false;
}

void cmd_eject(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    int nb_player_pushed = 0;

    sprintf(buffer, PEX_PATTERN, client->player->id);
    add_response(get_gui(head), buffer);
    for (client_t *tmp = head; tmp; tmp = tmp->next) {
        if (is_valid_player(head, client, game, tmp) == true) {
            nb_player_pushed++;
            sprintf(buffer, "eject: %d\n",
            eject(tmp->player, client->player->orientation, game->map));
            add_response(tmp, buffer);
            sprintf(buffer, PPO_PATTERN, tmp->player->id,
            tmp->player->coordinate.x, tmp->player->coordinate.y,
            tmp->player->orientation);
            add_response(get_gui(head), buffer);
        }
    }
    nb_player_pushed != 0 ?
    add_response(client, M_OK) : add_response(client, M_KO);
}
