/*
** EPITECH PROJECT, 2023
** players.c
** File description:
** players
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tools.h"
#include "game.h"

void check_duplicate_teams(team_t * const teams, const char * const team_name)
{
    team_t *tmp = NULL;

    for (tmp = teams; tmp; tmp = tmp->next)
        if (!strcmp(tmp->team_name, team_name))
            PERROR("Duplicate team names.");
}

int nb_teams(const char * const * const av)
{
    int start_idx = FAIL;

    for (int i = 1; av[i]; ++i) {
        !strcmp(av[i], "-n") && start_idx == FAIL ? start_idx = i : 0;
        if (!strcmp(av[i], "-c") && start_idx != FAIL
        && i - start_idx - 1 != 1 && i - start_idx - 1 != 0)
            return i - start_idx - 1;
    }
    PERROR_FLAG("-n");
}

static team_t *set_data_new_team(char * const team_name, const int max_slots)
{
    team_t *new_team = malloc(sizeof(team_t));
    CERROR(new_team == NULL, "malloc");

    new_team->available_slots = max_slots;
    new_team->team_name = team_name;
    new_team->next = NULL;
    return new_team;
}

static team_t *add_team_to_others(team_t * const head, team_t *new_team)
{
    team_t *tmp;
    new_team->next = NULL;

    if (head == NULL)
        return new_team;
    for (tmp = head; tmp->next; tmp = tmp->next);
    tmp->next = new_team;
    return head;
}

void create_team(team_t ** const head,
char * const team_name, const int max_slots)
{
    team_t *new_team = set_data_new_team(team_name, max_slots);
    *head = add_team_to_others(*head, new_team);
}
