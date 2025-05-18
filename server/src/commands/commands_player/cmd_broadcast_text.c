/*
** EPITECH PROJECT, 2023
** player_broadcast_text.c
** File description:
** player_broadcast_text
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "management.h"
#include "network.h"
#include "game.h"

int find_tile_number(player_t * const sender,
player_t * const receiver, game_t * const game)
{
    int dx = sender->coordinate.x - receiver->coordinate.x;
    int dy = sender->coordinate.y - receiver->coordinate.y;

    dx = (abs(dx) > game->map->width / 2) ?
    ((dx > 0) ? dx - game->map->width : dx + game->map->width) : dx;
    dy = (abs(dy) > game->map->height / 2) ?
    ((dy > 0) ? dy - game->map->height : dy + game->map->height) : dy;

    double angle = atan2(dy, dx) * 180 / PI + 180;
    angle -= receiver->orientation * 90;
    angle = (angle < 0) ? angle + 360 : ((angle >= 360) ? angle - 360 : angle);

    return (dx == 0 && dy == 0) ? 0 :
    (angle >= 337.5 || angle < 22.5) ? 1 :
    (angle >= 22.5 && angle < 67.5) ? 8 :
    (angle >= 67.5 && angle < 112.5) ? 7 :
    (angle >= 112.5 && angle < 157.5) ? 6 :
    (angle >= 157.5 && angle < 202.5) ? 5 :
    (angle >= 202.5 && angle < 247.5) ? 4 :
    (angle >= 247.5 && angle < 292.5) ? 3 : 2;
}

void cmd_broadcast_text(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];

    if (!client->queue.head->command.arg)
        return add_response(client, M_KO);
    sprintf(buffer, PBC_PATTERN, client->player->id,
    client->queue.head->command.arg);
    add_response(get_gui(head), buffer);
    for (client_t *tmp = head; tmp; tmp = tmp->next) {
        if (tmp->status != GUI && tmp->player->status != EGG &&
        tmp->player->id != client->player->id) {
            int tile_num =
            find_tile_number(client->player, tmp->player ,game);
            snprintf(buffer, sizeof(buffer),
            "message %d, %s\n", tile_num, client->queue.head->command.arg);
            add_response(tmp, buffer);
        }
    }
    add_response(client, M_OK);
}
