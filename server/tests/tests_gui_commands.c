/*
** EPITECH PROJECT, 2023
** tests_gui_commands.c
** File description:
** tests_gui_commands
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "init.h"
#include "game.h"

client_t *set_data_new_client(const int new_fd);
game_t *create_mock_game(int width, int height);
client_t *create_mock_client(int id, client_status_e status);
player_t *create_mock_player(int x, int y, orientation_e orientation);

//BCT
Test(cmd_functions_tests, check_cmd_bct)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);
    map_t *map = create_map(10, 10);
    game->map = map;

    client->queue.head = (node_t *) malloc(sizeof(node_t));
    client->queue.head->command.arg = strdup("bct 5 5");
    client->queue.head->next = NULL;

    game->map->tile[5][5].food = 3;
    game->map->tile[5][5].linemate = 2;
    game->map->tile[5][5].deraumere = 1;
    game->map->tile[5][5].sibur = 4;
    game->map->tile[5][5].mendiane = 0;
    game->map->tile[5][5].phiras = 6;
    game->map->tile[5][5].thystame = 7;

    char expected_buffer[BUFFER_SIZE];
    sprintf(expected_buffer, BCT_PATTERN, 5, 5, 3, 2, 1, 4, 0, 6, 7);

    cmd_bct(NULL, client, game);

    cr_assert_str_eq(client->write_buf[0], expected_buffer);
    free(client->queue.head->command.arg);
    free(client->queue.head);
}

//MCT
Test(cmd_functions_tests, check_cmd_mct)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);
    map_t *map = create_map(10, 10);

    game->map = map;
    game->map->height = 2;
    game->map->width = 2;

    for(int i = 0; i < game->map->height; i++) {
        for(int j = 0; j < game->map->width; j++) {
            game->map->tile[j][i].food = i + j;
            game->map->tile[j][i].linemate = i + j + 1;
            game->map->tile[j][i].deraumere = i + j + 2;
            game->map->tile[j][i].sibur = i + j + 3;
            game->map->tile[j][i].mendiane = i + j + 4;
            game->map->tile[j][i].phiras = i + j + 5;
            game->map->tile[j][i].thystame = i + j + 6;
        }
    }
    cmd_mct(NULL, client, game);
    char expected_buffer[BUFFER_SIZE];
    for(int i = 0; i < game->map->height; i++) {
        for(int j = 0; j < game->map->width; j++) {
            sprintf(expected_buffer, BCT_PATTERN, j, i, i+j, i+j+1, i+j+2, i+j+3, i+j+4, i+j+5, i+j+6);
            cr_assert_str_eq(client->write_buf[i * game->map->width + j], expected_buffer);
        }
    }
}

//MSZ
Test(cmd_functions_tests, check_cmd_msz)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);

    game->map->width = 10;
    game->map->height = 20;

    cmd_msz(NULL, client, game);

    char expected_buffer[BUFFER_SIZE];
    sprintf(expected_buffer, MSZ_PATTERN, game->map->width, game->map->height);
    cr_assert_str_eq(client->write_buf[0], expected_buffer);
}

//PIN
Test(cmd_functions_tests, check_cmd_pin)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(5, 7, N);
    player->id = 2;
    player->coordinate.x = 5;
    player->coordinate.y = 7;
    player->inventory.food = 10;
    player->inventory.linemate = 20;
    player->inventory.deraumere = 30;
    player->inventory.sibur = 40;
    player->inventory.mendiane = 50;
    player->inventory.phiras = 60;
    player->inventory.thystame = 70;
    game->player = player;
    char input[] = "pin #2";
    client->queue.head = malloc(sizeof(command_t));
    client->queue.head->command.arg = input;
    cmd_pin(NULL, client, game);

    char expected_buffer[BUFFER_SIZE];
    sprintf(expected_buffer, PIN_PATTERN, player->id, player->coordinate.x, player->coordinate.y,
    player->inventory.food, player->inventory.linemate, player->inventory.deraumere,
    player->inventory.sibur, player->inventory.mendiane, player->inventory.phiras,
    player->inventory.thystame);
    cr_assert_str_eq(client->write_buf[0], expected_buffer);
}

//PLV
Test(cmd_functions_tests, check_cmd_plv)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);

    player_t *player = create_mock_player(0, 0, N);
    player->id = 2;
    player->level = 4;
    game->player = player;

    char input[] = "plv #2";
    client->queue.head = malloc(sizeof(command_t));
    client->queue.head->command.arg = input;

    cmd_plv(NULL, client, game);

    char expected_buffer[BUFFER_SIZE];
    sprintf(expected_buffer, PLV_PATTERN, player->id, player->level);

    cr_assert_str_eq(client->write_buf[0], expected_buffer);
}

//PPO
Test(cmd_functions_tests, check_cmd_ppo)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);

    player_t *player = create_mock_player(10, 10, N);
    player->id = 2;
    player->coordinate.x = 5;
    player->coordinate.y = 7;
    player->orientation = 1;
    game->player = player;

    char input[] = "ppo #2";
    client->queue.head = malloc(sizeof(command_t));
    client->queue.head->command.arg = input;

    cmd_ppo(NULL, client, game);

    char expected_buffer[BUFFER_SIZE];
    sprintf(expected_buffer, PPO_PATTERN, player->id, player->coordinate.x,
            player->coordinate.y, player->orientation);

    cr_assert_str_eq(client->write_buf[0], expected_buffer);
}

//SGT
Test(cmd_functions_tests, check_cmd_sgt)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);
    game->freq = 10;

    cmd_sgt(NULL, client, game);

    char expected_buffer[BUFFER_SIZE];
    sprintf(expected_buffer, SGT_PATTERN, game->freq);

    cr_assert_str_eq(client->write_buf[0], expected_buffer);
}

//SST
Test(cmd_functions_tests, check_cmd_sst)
{
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);
    cmd_sst(NULL, client, game);
    cr_assert_eq(true, true);
}

//TNA
Test(cmd_functions_tests, check_cmd_tna)
{
    team_t *team = NULL;
    client_t *client = create_mock_client(1, GUI);
    game_t *game = create_mock_game(10, 10);

    create_team(&team, "Team1", 1);
    create_team(&team, "Team2", 1);
    create_team(&team, "Team3", 1);
    game->team = team;

    cmd_tna(NULL, client, game);

    char expected_buffer1[BUFFER_SIZE];
    char expected_buffer2[BUFFER_SIZE];
    char expected_buffer3[BUFFER_SIZE];
    sprintf(expected_buffer1, TNA_PATTERN, "Team1");
    sprintf(expected_buffer2, TNA_PATTERN, "Team2");
    sprintf(expected_buffer3, TNA_PATTERN, "Team3");

    cr_assert_str_eq(client->write_buf[0], expected_buffer1);
    cr_assert_str_eq(client->write_buf[1], expected_buffer2);
    cr_assert_str_eq(client->write_buf[2], expected_buffer3);
}
