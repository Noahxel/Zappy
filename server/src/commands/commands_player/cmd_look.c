/*
** EPITECH PROJECT, 2023
** player_look.c
** File description:
** player_look
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "tools.h"
#include "game.h"

static void look_up(const player_t * const player,
const game_t * const game, char * const * const buffer)
{
    char *tmp = get_tile_resources
    (game->player, game->map, player->coordinate.x, player->coordinate.y);
    sprintf(*buffer, "[%s,", tmp);
    free(tmp);

    for (int i = 1; i <= player->level; i++)
        for (int j = -i; j <= i; j++) {
            int x = (player->coordinate.x + j +
            game->map->width) % game->map->width;
            int y = (player->coordinate.y - i +
            game->map->height) % game->map->height;
            tmp = get_tile_resources(game->player, game->map, x, y);
            strcat(*buffer, tmp);
            free(tmp);
            strcat(*buffer, ",");
        }
    if ((*buffer)[strlen(*buffer) - 1] == ',')
        (*buffer)[strlen(*buffer) - 1] = '\0';
    strcat(*buffer, "]\n");
}

static void look_down(const player_t * const player,
const game_t * const game, char * const * const buffer)
{
    char *tmp = get_tile_resources
    (game->player, game->map, player->coordinate.x, player->coordinate.y);
    sprintf(*buffer, "[%s,", tmp);
    free(tmp);

    for (int i = 1; i <= player->level; i++) {
        for (int j = i; j >= -i; j--) {
            int x = (player->coordinate.x + j +
            game->map->width) % game->map->width;
            int y = (player->coordinate.y + i) %
            game->map->height;
            tmp = get_tile_resources(game->player, game->map, x, y);
            strcat(*buffer, tmp);
            free(tmp);
            strcat(*buffer, ",");
        }
    }
    if ((*buffer)[strlen(*buffer) - 1] == ',')
        (*buffer)[strlen(*buffer) - 1] = '\0';
    strcat(*buffer, "]\n");
}

static void look_right(const player_t * const player,
const game_t * const game, char * const * const buffer)
{
    char *tmp = get_tile_resources
    (game->player, game->map, player->coordinate.x, player->coordinate.y);
    sprintf(*buffer, "[%s,", tmp);
    free(tmp);

    for (int i = 1; i <= player->level; i++)
        for (int j = -i; j <= i; j++) {
            int x = (player->coordinate.x + i +
            game->map->width) % game->map->width;
            int y = (player->coordinate.y + j +
            game->map->height) % game->map->height;
            tmp = get_tile_resources(game->player, game->map, x, y);
            strcat(*buffer, tmp);
            free(tmp);
            strcat(*buffer, ",");
        }
    if ((*buffer)[strlen(*buffer) - 1] == ',')
        (*buffer)[strlen(*buffer) - 1] = '\0';
    strcat(*buffer, "]\n");
}

static void look_left(const player_t * const player,
const game_t * const game, char * const * const buffer)
{
    char *tmp = get_tile_resources
    (game->player, game->map, player->coordinate.x, player->coordinate.y);
    sprintf(*buffer, "[%s,", tmp);
    free(tmp);

    for (int i = 1; i <= player->level; i++)
        for (int j = i; j >= -i; j--) {
            int x = (player->coordinate.x - i +
            game->map->width) % game->map->width;
            int y = (player->coordinate.y + j +
            game->map->height) % game->map->height;
            tmp = get_tile_resources(game->player, game->map, x, y);
            strcat(*buffer, tmp);
            free(tmp);
            strcat(*buffer, ",");
        }
    if ((*buffer)[strlen(*buffer) - 1] == ',')
        (*buffer)[strlen(*buffer) - 1] = '\0';
    strcat(*buffer, "]\n");
}

void cmd_look(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));

    client->player->orientation == N ?
    look_up(client->player, game, &buffer) :
    client->player->orientation == S ?
    look_down(client->player, game, &buffer) :
    client->player->orientation == E ?
    look_right(client->player, game, &buffer) :
    client->player->orientation == W ?
    look_left(client->player, game, &buffer) : 0;
    add_response(client, buffer);
    free(buffer);
}
