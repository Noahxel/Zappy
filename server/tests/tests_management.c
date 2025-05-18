/*
** EPITECH PROJECT, 2023
** tests_managements.c
** File description:
** tests_management
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

// Assignment
Test(assignment_functions_tests, check_assignment_to_team)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *gui = create_mock_client(1, GUI);
    client_t *client = create_mock_client(2, NONE);
    player_t *player = create_mock_player(1, 1, N);
    client->commands = malloc(2 * sizeof(char *));
    create_team(&team, "Team1", 1);
    player->status = UNAFFECTED;
    player->team = team;
    game->player = player;
    game->given_id = 0;
    client->commands[0] = strdup("Team1");

    assignment_to_team(gui, client, game);

    cr_assert_eq(client->status, PLAYER);
    cr_assert_eq(client->player, player);
    cr_assert_eq(player->status, ALIVE);
    cr_assert_eq(player->team->available_slots, 0);
    cr_assert_str_eq(gui->write_buf[0], "pnw #1 1 1 1 0 Team1\n");
}

Test(assignment_functions_tests, check_assignment_to_team_egg)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *gui = create_mock_client(1, GUI);
    client_t *client = create_mock_client(2, NONE);
    player_t *player = create_mock_player(1, 1, N);
    client->commands = malloc(2 * sizeof(char *));
    create_team(&team, "Team1", 1);
    player->status = EGG;
    player->team = team;
    game->player = player;
    game->given_id = 0;
    client->commands[0] = strdup("Team1");

    assignment_to_team(gui, client, game);

    cr_assert_eq(client->status, PLAYER);
    cr_assert_eq(client->player, player);
    cr_assert_eq(player->status, ALIVE);
    cr_assert_eq(player->team->available_slots, 0);
    cr_assert_str_eq(gui->write_buf[0], "ebo 0\n");
}

Test(assignment_functions_tests, check_assignment_to_gui)
{
    client_t *client = create_mock_client(1, NONE);
    bool is_there_gui = false;

    assignment_to_gui(client, &is_there_gui);

    cr_assert_eq(client->status, GUI);
    cr_assert_eq(is_there_gui, true);

    client_t *client2 = create_mock_client(2, NONE);
    assignment_to_gui(client2, &is_there_gui);

    cr_assert_eq(client2->status, INVALID);
    cr_assert_str_eq(client2->write_buf[0], M_KO);
}

Test(assignment_functions_tests, check_assignment_to_team_invalid)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *gui = create_mock_client(1, GUI);
    client_t *client = create_mock_client(2, NONE);
    player_t *player = create_mock_player(1, 1, N);
    client->commands = malloc(2 * sizeof(char *));
    create_team(&team, "Team1", 1);
    player->status = EGG;
    player->status = UNAFFECTED;
    player->team = team;
    game->player = player;
    game->given_id = 0;
    client->commands[0] = strdup("Team2");

    assignment_to_team(gui, client, game);

    cr_assert_eq(client->status, INVALID);
    cr_assert_str_eq(client->write_buf[0], M_KO);
}

// Egg
Test(egg_creation, create_egg)
{
    team_t *team = NULL;
    player_t *head = NULL;
    create_team(&team, "team1", 1);
    map_t *map = create_map(10, 10);
    int id = 1;

    create_egg(&head, team, map, id);

    cr_assert_not_null(head);
    cr_assert_eq(head->id, id);
    cr_assert_eq(head->team, team);
    cr_assert_eq(head->status, EGG);
    cr_assert_eq(head->level, 1);
    cr_assert(head->coordinate.x >= 0 && head->coordinate.x < 10);
    cr_assert(head->coordinate.y >= 0 && head->coordinate.y < 10);
}

// Incantation
Test(cmd_functions_tests, check_cmd_incantation_valid_not_enough_players)
{
    client_t *head = create_mock_client(1, GUI);
    client_t *client = create_mock_client(2, PLAYER);
    game_t *game = create_mock_game(10, 10);
    map_t *map = create_map(10, 10);
    head->next = client;

    client->player->coordinate.x = 0;
    client->player->coordinate.y = 0;
    client->player->level = 2;
    client->player->status = ALIVE;
    game->map = map;
    game->player = client->player;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].linemate = 1;
    cmd_incantation(head, client, game);
    cr_assert_eq(client->write_buf[0], client->write_buf[0]);
}

// Map
Test(game, invalid_size, .exit_code = ERROR)
{
    create_map(1, 1);
}

Test(game, test_compare_tile)
{
    team_t *team = NULL;
    create_team(&team, "Team1", 1);
    game_t *game = create_mock_game(10, 10);
    player_t *player1 = create_mock_player(1, 1, N);
    player_t *player2 = create_mock_player(1, 1, S);
    map_t *map = create_map(10, 10);
    map_t *tmp = map;
    game->map = map;
    player1->team = team;
    player2->team = team;
    game->player = player1;
    game->player->next = player2;
    int x = 1;
    int y = 1;

    cr_assert(compare_tile(game, tmp, x, y) == true);
}

Test(game, test_copy_map)
{
    map_t *original = create_map(10, 10);
    map_t *copy = copy_map(original);

    for (int i = 0; i < original->width; i++)
    {
        for (int j = 0; j < original->height; j++)
        {
            cr_assert(copy->tile[i][j].food == original->tile[i][j].food);
            cr_assert(copy->tile[i][j].deraumere == original->tile[i][j].deraumere);
            cr_assert(copy->tile[i][j].linemate == original->tile[i][j].linemate);
            cr_assert(copy->tile[i][j].mendiane == original->tile[i][j].mendiane);
            cr_assert(copy->tile[i][j].phiras == original->tile[i][j].phiras);
            cr_assert(copy->tile[i][j].sibur == original->tile[i][j].sibur);
            cr_assert(copy->tile[i][j].thystame == original->tile[i][j].thystame);
        }
    }
}

Test(game, test_give_map_coordinate)
{
    int width = 10;
    int height = 10;

    coordinate_t coordinates = give_map_coordinate(width, height);

    cr_assert(coordinates.x >= 0 && coordinates.x < width);
    cr_assert(coordinates.y >= 0 && coordinates.y < height);
}

// Map
Test(game, tests_ensure_min_resources)
{
    map_t *map = create_map(10, 10);
    int count = 0;

    for (int i = 0; i < map->width; i++)
        for (int j = 0; j < map->height; j++)
        {
            map->tile[i][j].food = 0;
            map->tile[i][j].deraumere = 0;
            map->tile[i][j].linemate = 0;
            map->tile[i][j].mendiane = 0;
            map->tile[i][j].phiras = 0;
            map->tile[i][j].sibur = 0;
            map->tile[i][j].thystame = 0;
        }
    ensure_min_resources(map);
    for (int i = 0; i < map->width; i++)
        for (int j = 0; j < map->height; j++)
        {
            map->tile[i][j].food > 0 ? count++ : 0;
            map->tile[i][j].deraumere > 0 ? count++ : 0;
            map->tile[i][j].linemate > 0 ? count++ : 0;
            map->tile[i][j].mendiane > 0 ? count++ : 0;
            map->tile[i][j].phiras > 0 ? count++ : 0;
            map->tile[i][j].sibur > 0 ? count++ : 0;
            map->tile[i][j].thystame > 0 ? count++ : 0;
        }
    cr_assert_eq(count, 7);
}

// Client
Test(management, test_disconnect_client)
{
    int fd1 = 1;
    int fd2 = 2;

    client_t *head = NULL;
    create_client(&head, fd1);
    create_client(&head, fd2);

    cr_assert(head != NULL);
    cr_assert(head->fd == fd1);
    cr_assert(head->next != NULL);
    cr_assert(head->next->fd == fd2);

    disconnect_client(&head, head->next);

    cr_assert(head != NULL);
    cr_assert(head->fd == fd1);
}

Test(management, test_create_client)
{
    int fd = 1;

    client_t *head = NULL;
    create_client(&head, fd);

    cr_assert(head != NULL);
    cr_assert(head->fd == fd);
}

// Queue
Test(node_creation, test_node)
{
    command_t cmd = {"test_cmd", NULL, "test_arg", 0};
    node_t *node = malloc(sizeof(node_t));
    node->command = cmd;
    node->next = NULL;

    cr_assert_str_eq(node->command.name, "test_cmd");
    cr_assert_str_eq(node->command.arg, "test_arg");
    cr_assert_eq(node->command.waiting_time, 0);
    cr_assert_null(node->next);
    free(node);
}

Test(queue_creation, test_queue)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    cr_assert_null(queue->head);
    cr_assert_null(queue->tail);
    cr_assert_eq(queue->size, 0);
    free(queue);
}

Test(queue_operations, enqueue)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    command_t cmd = {"test_cmd", NULL, strdup("test_arg"), 0};
    enqueue(queue, cmd);

    cr_assert_not_null(queue->head);
    cr_assert_not_null(queue->tail);
    cr_assert_eq(queue->size, 1);
    cr_assert_str_eq(queue->head->command.name, "test_cmd");
    cr_assert_str_eq(queue->head->command.arg, "test_arg");
    free_queue(queue);
}

Test(queue_operations, dequeue)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    command_t cmd1 = {"test_cmd1", NULL, strdup("test_arg1"), 0};
    command_t cmd2 = {"test_cmd2", NULL, strdup("test_arg2"), 0};
    enqueue(queue, cmd1);
    enqueue(queue, cmd2);

    cr_assert_str_eq(queue->head->command.name, "test_cmd1");
    dequeue(queue);
    cr_assert_eq(queue->size, 1);
    cr_assert_str_eq(queue->head->command.name, "test_cmd2");
    free_queue(queue);
}

Test(queue_operations, dequeue_empty)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    dequeue(queue);
    cr_assert_eq(SUCCESS, SUCCESS);
}

Test(queue_operations, free_queue)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    command_t cmd1 = {"test_cmd1", NULL, strdup("test_arg1"), 0};
    command_t cmd2 = {"test_cmd2", NULL, strdup("test_arg2"), 0};
    enqueue(queue, cmd1);
    enqueue(queue, cmd2);

    free_queue(queue);
    cr_assert_eq(queue->size, 0);
    cr_assert_null(queue->head);
    cr_assert_null(queue->tail);
}

Test(queue_operations, get_head)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    command_t cmd1 = {"test_cmd1", NULL, strdup("test_arg1"), 0};
    command_t cmd2 = {"test_cmd2", NULL, strdup("test_arg2"), 0};
    enqueue(queue, cmd1);
    enqueue(queue, cmd2);

    cr_assert_str_eq(queue->head->command.name, "test_cmd1");
    command_t head = get_head(queue);
    cr_assert_eq(queue->size, 2);
    cr_assert_str_eq(head.name, "test_cmd1");
    free_queue(queue);
}

Test(queue_operations, get_head_empty)
{
    queue_t *queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    command_t head = get_head(queue);
    cr_assert_eq(head.name, NULL);
    cr_assert_eq(head.cmd_function, NULL);
    cr_assert_eq(head.arg, NULL);
    cr_assert_eq(head.waiting_time, 0);
    free_queue(queue);
}
