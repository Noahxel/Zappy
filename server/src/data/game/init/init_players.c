/*
** EPITECH PROJECT, 2023
** init_players.c
** File description:
** init_players
*/

#include "management.h"
#include "game.h"

player_t *init_players(const map_t * const map,
team_t * const team, const int nb_clients_per_team)
{
    player_t *player = NULL;

    for (team_t *tmp = team; tmp; tmp = tmp->next)
        for (int i = 0; i < nb_clients_per_team; ++i)
            create_player(&player, tmp, map, 0);
    return player;
}
