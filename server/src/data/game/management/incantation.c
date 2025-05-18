/*
** EPITECH PROJECT, 2023
** incantation.c
** File description:
** incantation
*/

#include "management.h"
#include "game.h"

static int nb_players_of_same_level(const game_t * const game,
player_t * const player)
{
    int nb_players_of_same_level = 0;

    for (player_t *tmp = game->player; tmp; tmp = tmp->next)
        if (IS_SAME_COORD(tmp->coordinate, player->coordinate) &&
        tmp->level >= player->level)
            nb_players_of_same_level++;
    return nb_players_of_same_level;
}

static int nb_type_of_stone(const resource_t res, const int stone_type)
{
    return stone_type == LINEMATE ? res.linemate :
    stone_type == DERAUMERE ? res.deraumere :
    stone_type == SIBUR ? res.sibur :
    stone_type == MENDIANE ? res.mendiane :
    stone_type == PHIRAS ? res.phiras :
    stone_type == THYSTAME ? res.thystame : 0;
}

bool is_incantation_valid(const game_t * const game, player_t * const player)
{
    const int *actual_rule = INCANTATION_RULES[player->level - 1];
    resource_t res = game->map->tile
    [player->coordinate.x][player->coordinate.y];

    if (nb_players_of_same_level(game, player) < actual_rule[NB_PLAYERS])
        return false;
    for (int i = LINEMATE; i <= THYSTAME; i++)
        if (nb_type_of_stone(res, i) < actual_rule[i])
            return false;
    return true;
}
