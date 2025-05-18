/*
** EPITECH PROJECT, 2023
** tests_tools.c
** File description:
** tests_tools
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "management.h"
#include "network.h"
#include "init.h"
#include "game.h"

Test(init_freq, test_init_flag_invalid_value)
{
    int f = 0;
    const char *const av[] = {"program", "-f", "-10", NULL};
    f = init_freq(av, "-f");
    cr_assert_eq(f, 100);
}

Test(check_duplicate_teams, test_check_duplicate_teams, .exit_code = ERROR)
{
    team_t team1 = {.team_name = "team1", .next = NULL};
    team_t team2 = {.team_name = "team1", .next = &team1};

    check_duplicate_teams(&team2, "team1");
}

Test(add_response, test_add_response_empty_message)
{
    client_t client = {.write_buf = NULL};
    const char *const message = "";

    add_response(&client, message);
    cr_assert_str_eq(client.write_buf[0], message);
    my_free_array(client.write_buf);
}

Test(add_response, test_add_response_non_empty_message)
{
    client_t client = {.write_buf = NULL};
    const char *const message = "Hello, world!";

    add_response(&client, message);
    cr_assert_str_eq(client.write_buf[0], message);
    my_free_array(client.write_buf);
}

Test(add_response, test_add_response_non_empty_message_2)
{
    client_t client = {.write_buf = NULL};
    const char *const message1 = "Hello, world1!";
    const char *const message2 = "Hello, world2!";

    add_response(&client, message1);
    add_response(&client, message2);
    cr_assert_str_eq(client.write_buf[1], message2);
    my_free_array(client.write_buf);
}

Test(nb_teams, test_nb_teams)
{
    const char *const av[] = {"program", "-n", "team1", "team2", "-c", "2", NULL};
    int num_teams = nb_teams(av);

    cr_assert_eq(num_teams, 2);
}

Test(nb_teams, test_nb_teams_no_teams, .exit_code = ERROR)
{
    const char *const av[] = {"program", "-c", "2", NULL};
    nb_teams(av);
}

Test(get_flag, test_get_flag)
{
    const char *const av[] = {"program", "-f", "10", NULL};

    int f = get_flag(av, "-f");
    cr_assert_eq(f, 10);
}

Test(get_flag, test_get_flag_no_flag, .exit_code = ERROR)
{
    const char *const av[] = {"program", NULL};

    get_flag(av, "-f");
}

Test(get_resource_counts, test_get_resource_counts)
{
    map_t map;
    map.tile = malloc(sizeof(resource_t *));
    map.tile[0] = malloc(sizeof(resource_t));
    map.tile[0][0].food = 5;
    map.tile[0][0].linemate = 2;
    map.tile[0][0].deraumere = 1;
    map.tile[0][0].sibur = 0;
    map.tile[0][0].mendiane = 0;
    map.tile[0][0].phiras = 3;
    map.tile[0][0].thystame = 2;
    int *resource_counts = get_resource_counts(&map, 0, 0);

    cr_assert_eq(resource_counts[R_FOOD], 5);
    cr_assert_eq(resource_counts[R_LINEMATE], 2);
    cr_assert_eq(resource_counts[R_DERAUMERE], 1);
    cr_assert_eq(resource_counts[R_SIBUR], 0);
    cr_assert_eq(resource_counts[R_MENDIANE], 0);
    cr_assert_eq(resource_counts[R_PHIRAS], 3);
    cr_assert_eq(resource_counts[R_THYSTAME], 2);

    free(map.tile[0]);
    free(map.tile);
}

Test(my_str_to_array, test_my_str_to_array)
{
    const char *const str = "Hello, world";
    const char *const delim = " ";

    char **array = my_str_to_array(str, delim);
    cr_assert_str_eq(array[0], "Hello,");
    cr_assert_str_eq(array[1], "world");
    my_free_array(array);
}

Test(my_str_to_array, test_my_str_to_array_break)
{
    const char *const str = "    ";
    const char *const delim = " ";

    char **array = my_str_to_array(str, delim);
    my_free_array(array);
}

Test(my_free_array, test_my_free_array)
{
    char **array = malloc(2 * sizeof(char *));
    array[0] = strdup("Hello,");
    array[1] = strdup("world!");

    my_free_array(array);
    array = NULL;
    cr_assert_null(array);
}
