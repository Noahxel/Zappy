/*
** EPITECH PROJECT, 2023
** tests_init.c
** File description:
** tests_init
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "management.h"
#include "game.h"
#include "init.h"

Test(init_inventory, test_init_inventory)
{
    resource_t inventory = create_inventory();
    cr_assert_eq(inventory.food, 10);
    cr_assert_eq(inventory.linemate, 0);
}

Test(init_teams, test_init_teams)
{
    const char * const av[] = {"program", "-n", "team1", "team2", NULL};
    size_t nb_teams = 2;
    team_t *teams = init_teams(av, nb_teams, 2);

    cr_assert_str_eq(teams->team_name, "team1");
    cr_assert_str_eq(teams->next->team_name, "team2");
    cr_assert_null(teams->next->next);
    free(teams->next);
    free(teams);
}

Test(init_map, test_init_map)
{
    map_t *map;
    map = create_map(10, 20);

    cr_assert_eq(map->width, 10);
    cr_assert_eq(map->height, 20);
}

Test(init_game, test_init_game)
{
    game_t *game = malloc(sizeof(game_t));
    const char * const av[] = {"program", "-x", "10", "-y", "20", "-n", "team1", "team2", "-c", "2", "-f", "2", NULL};
    init_game(av, game);

    cr_assert_eq(game->map->width, 10);
    cr_assert_eq(game->map->height, 20);
    cr_assert_eq(game->freq, 2);
    cr_assert_str_eq(game->team->team_name, "team1");
    free(game);
}