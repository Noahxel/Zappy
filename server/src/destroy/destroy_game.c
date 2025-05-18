/*
** EPITECH PROJECT, 2023
** destroy_game.c
** File description:
** destroy_game
*/

#include <stdlib.h>

#include "game.h"

static void destroy_player(player_t * const player)
{
    if (!player)
        return;
    destroy_player(player->next);
    free(player);
}

static void destroy_team(team_t * const team)
{
    if (!team)
        return;
    destroy_team(team->next);
    free(team);
}

void destroy_map(map_t * const map)
{
    if (!map)
        return;
    for (int i = 0; i < map->width; i++)
        free(map->tile[i]);
    free(map->tile);
    free(map);
}

void destroy_game(game_t game)
{
    destroy_player(game.player);
    destroy_team(game.team);
    destroy_map(game.map);
}
