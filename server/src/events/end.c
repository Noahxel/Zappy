/*
** EPITECH PROJECT, 2023
** end.c
** File description:
** end
*/

#include <string.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

static int count_players_at_max_level(player_t * const player_list,
const char * const team_name)
{
    int i = 0;

    for (player_t *tmp = player_list; tmp; tmp = tmp->next)
        if (strcmp(tmp->team->team_name, team_name) == 0 &&
        tmp->level >= MAX_LEVEL)
            i++;
    return i;
}

static char *find_potential_winning_team(player_t * const player_list)
{
    for (player_t *tmp = player_list; tmp; tmp = tmp->next)
        if (tmp->level >= MAX_LEVEL && count_players_at_max_level
        (player_list, tmp->team->team_name) >= NB_PLAYERS_FOR_WINNING)
            return tmp->team->team_name;
    return NULL;
}

static void update_clients_to_logout(client_t * const head)
{
    for (client_t *tmp = head; tmp; tmp = tmp->next)
        tmp->status = INVALID;
}

void handle_end_game(client_t * const head, const game_t * const game)
{
    char buffer[BUFFER_SIZE];
    char *winning_team = find_potential_winning_team(game->player);

    if (winning_team) {
        sprintf(buffer, SEG_PATTERN, winning_team);
        M_WINNER(get_gui(head)->fd, buffer);
        update_clients_to_logout(head);
    }
}
