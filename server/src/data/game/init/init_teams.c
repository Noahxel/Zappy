/*
** EPITECH PROJECT, 2023
** init_teams.c
** File description:
** init_teams
*/

#include <string.h>

#include "management.h"
#include "game.h"

team_t *init_teams(char * const * const av,
const int nb_teams, const int max_slots)
{
    int idx = -1;
    team_t *team = NULL;

    for (int i = 0; av[i] && idx == -1; ++i,
    (idx = !strcmp(av[i], "-n") ? i : idx));
    for (int i = 0; i < nb_teams; ++i) {
        check_duplicate_teams(team, av[idx + 1 + i]);
        create_team(&team, av[idx + 1 + i], max_slots);
    }
    return team;
}
