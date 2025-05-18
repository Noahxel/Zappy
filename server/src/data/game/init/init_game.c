/*
** EPITECH PROJECT, 2023
** init_game.c
** File description:
** init_game
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "management.h"
#include "tools.h"
#include "game.h"
#include "init.h"

void init_game(const char * const * const av, game_t * const game)
{
    game->given_id = 0;
    game->map = create_map(get_flag(av, "-x"), get_flag(av, "-y"));
    game->freq = init_freq(av, "-f");
    game->team = init_teams(av, nb_teams(av), get_flag(av, "-c"));
    game->player = init_players(game->map, game->team, get_flag(av, "-c"));
}
