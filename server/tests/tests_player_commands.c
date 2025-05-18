/*
** EPITECH PROJECT, 2023
** tests_player_commands.c
** File description:
** tests_player_commands
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "init.h"
#include "game.h"

int find_tile_number(player_t * const sender,
player_t * const receiver, game_t * const game);

client_t *set_data_new_client(const int new_fd)
{
    client_t *new_client = malloc(sizeof(client_t));
    CERROR(new_client == NULL, "malloc");

    new_client->fd = new_fd;
    new_client->queue.size = 0;
    new_client->queue.head = 0;
    new_client->queue.tail = 0;
    new_client->queue.head = NULL;
    new_client->queue.tail = NULL;
    new_client->status = NONE;
    new_client->commands = NULL;
    new_client->player = NULL;
    new_client->write_buf = NULL;
    new_client->next = NULL;
    return new_client;
}

player_t *create_mock_player(int x, int y, orientation_e orientation)
{
    player_t *player = malloc(sizeof(player_t));
    player->coordinate.x = x;
    player->coordinate.y = y;
    player->orientation = orientation;
    return player;
}

game_t *create_mock_game(int width, int height)
{
    game_t *game = malloc(sizeof(game_t));
    game->map = malloc(sizeof(map_t));
    game->map->width = width;
    game->map->height = height;
    return game;
}

team_t *create_mock_team(char *team_name, int max_slots)
{
    team_t *team = malloc(sizeof(team_t));
    team->team_name = team_name;
    team->available_slots = max_slots;
    team->next = NULL;
    return team;
}

client_t *create_mock_client(int id, client_status_e status)
{
    client_t *client = set_data_new_client(0);
    client->status = status;
    client->player = malloc(sizeof(player_t));
    client->player->id = id;
    client->player->coordinate.x = 0;
    client->player->coordinate.y = 0;
    client->player->orientation = N;
    return client;
}

command_t *create_mock_command(const char *name, void (*cmd_function)(client_t *, client_t *, game_t *), char *arg, int waiting_time)
{
    command_t *command = (command_t *)malloc(sizeof(command_t));
    if (command == NULL)
    {
        printf("Failed to allocate memory for mock command\n");
        return NULL;
    }

    command->name = name;
    command->cmd_function = cmd_function;
    command->arg = arg;
    command->waiting_time = waiting_time;

    return command;
}

node_t *create_mock_node(const char *name, void (*cmd_function)(client_t *, client_t *, game_t *), char *arg, int waiting_time)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        printf("Failed to allocate memory for mock node\n");
        return NULL;
    }

    node->command.name = name;
    node->command.cmd_function = cmd_function;
    node->command.arg = arg;
    node->command.waiting_time = waiting_time;
    node->next = NULL;

    return node;
}

// sound direction
Test(tile_number, same_position)
{
    player_t *sender = create_mock_player(5, 2, E);
    player_t *receiver = create_mock_player(5, 2, E);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 0);
}

Test(tile_number, different_position1)
{
    player_t *sender = create_mock_player(5, 2, E);
    player_t *receiver = create_mock_player(2, 9, N);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 6);
}

Test(tile_number, different_position2)
{
    player_t *sender = create_mock_player(5, 2, E);
    player_t *receiver = create_mock_player(2, 9, W);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 4);
}

Test(tile_number, different_position3)
{
    player_t *sender = create_mock_player(5, 2, E);
    player_t *receiver = create_mock_player(2, 9, S);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 2);
}

Test(tile_number, different_position4)
{
    player_t *sender = create_mock_player(5, 2, E);
    player_t *receiver = create_mock_player(2, 9, E);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 8);
}

Test(tile_number, different_position5)
{
    player_t *sender = create_mock_player(0, 0, E);
    player_t *receiver = create_mock_player(8, 8, N);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 6);
}

Test(tile_number, different_position6)
{
    player_t *sender = create_mock_player(2, 1, E);
    player_t *receiver = create_mock_player(2, 9, N);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 5);
}

Test(tile_number, different_position7)
{
    player_t *sender = create_mock_player(2, 1, E);
    player_t *receiver = create_mock_player(3, 9, N);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 5);
}


Test(tile_number, different_position8)
{
    player_t *sender = create_mock_player(2, 1, E);
    player_t *receiver = create_mock_player(3, 9, S);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 1);
}

Test(tile_number, different_position9)
{
    player_t *sender = create_mock_player(2, 1, E);
    player_t *receiver = create_mock_player(4, 9, N);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 4);
}

Test(tile_number, different_position10)
{
    player_t *sender = create_mock_player(2, 5, E);
    player_t *receiver = create_mock_player(7, 5, N);
    game_t *game = create_mock_game(10, 11);

    int tile_number = find_tile_number(sender, receiver, game);
    cr_assert_eq(tile_number, 3);
}

// broadcast
Test(cmd_broadcast_text, broadcasts_message)
{
    client_t *client1 = create_mock_client(1, PLAYER);
    client_t *client2 = create_mock_client(2, PLAYER);
    client_t *head = create_mock_client(0, GUI);
    head->next = client1;
    client1->next = client2;
    game_t *game = create_mock_game(10, 10);
    node_t *node = malloc(sizeof(node_t));
    node->command.arg = "Test message";
    client1->queue.head = node;

    cmd_broadcast_text(head, client1, game);
    cr_assert_str_eq(client2->write_buf[0], "message 0, Test message\n");
    free(node);
}

Test(cmd_broadcast_text, no_broadcasts_message)
{
    client_t *client1 = create_mock_client(1, PLAYER);
    client_t *client2 = create_mock_client(2, PLAYER);
    client_t *head = create_mock_client(0, GUI);
    head->next = client1;
    client1->next = client2;
    game_t *game = create_mock_game(10, 10);
    node_t *node = malloc(sizeof(node_t));
    node->command.arg = NULL;
    client1->queue.head = node;

    cmd_broadcast_text(head, client1, game);
    cr_assert_str_eq(client1->write_buf[0], M_KO);
    free(node);
}


// Connect_nbr
Test(cmd_connect_nbr, sends_available_slots)
{
    client_t *client = create_mock_client(1, PLAYER);
    player_t *test = create_mock_player(9, 9, N);
    game_t *game = create_mock_game(10, 10);
    team_t *team1 = create_mock_team("Team1", 3);
    team_t *team2 = create_mock_team("Team2", 2);
    test->team = team1;
    client->player = test;
    game->team = team1;
    team1->next = team2;

    cmd_connect_nbr(NULL, client, game);
    cr_assert_str_eq(client->write_buf[0], "3\n");
}

// eject
Test(cmd_eject, ejects_player_in_same_coordinate_1)
{
    game_t *game = create_mock_game(10, 10);
    client_t *head = create_mock_client(1, PLAYER);
    client_t *client1 = create_mock_client(2, PLAYER);
    head->next = client1;

    cmd_eject(head, head, game);
    cr_assert_str_eq(client1->write_buf[0], "eject: 3\n");
    cr_assert_eq(client1->player->coordinate.x, 0);
    cr_assert_eq(client1->player->coordinate.y, 9);
}

Test(cmd_eject, ejects_player_in_same_coordinate_2)
{
    game_t *game = create_mock_game(10, 10);
    client_t *head = create_mock_client(1, PLAYER);
    head->player->orientation = S;
    client_t *client1 = create_mock_client(2, PLAYER);
    head->next = client1;

    cmd_eject(head, head, game);
    cr_assert_str_eq(client1->write_buf[0], "eject: 1\n");
    cr_assert_eq(client1->player->coordinate.x, 0);
    cr_assert_eq(client1->player->coordinate.y, 1);
}

Test(cmd_eject, ejects_player_in_same_coordinate_3)
{
    game_t *game = create_mock_game(10, 10);
    client_t *head = create_mock_client(1, PLAYER);
    head->player->orientation = E;
    client_t *client1 = create_mock_client(2, PLAYER);
    head->next = client1;

    cmd_eject(head, head, game);
    cr_assert_str_eq(client1->write_buf[0], "eject: 4\n");
    cr_assert_eq(client1->player->coordinate.x, 1);
    cr_assert_eq(client1->player->coordinate.y, 0);
}

Test(cmd_eject, ejects_player_in_same_coordinate_4)
{
    game_t *game = create_mock_game(10, 10);
    client_t *head = create_mock_client(1, PLAYER);
    head->player->orientation = W;
    client_t *client1 = create_mock_client(2, PLAYER);
    head->next = client1;

    cmd_eject(head, head, game);
    cr_assert_str_eq(client1->write_buf[0], "eject: 2\n");
    cr_assert_eq(client1->player->coordinate.x, 9);
    cr_assert_eq(client1->player->coordinate.y, 0);
}

Test(cmd_eject, ejects_player_in_same_coordinate_5)
{
    game_t *game = create_mock_game(10, 10);
    client_t *head = create_mock_client(1, PLAYER);
    head->player->coordinate.x = 1;
    client_t *client1 = create_mock_client(2, PLAYER);
    head->next = client1;

    cmd_eject(head, head, game);
    cr_assert_str_eq(head->write_buf[0], M_KO);
}

Test(cmd_eject, ejects_player_in_same_coordinate_gui)
{
    game_t *game = create_mock_game(10, 10);
    client_t *head = create_mock_client(1, GUI);
    client_t *client1 = create_mock_client(2, PLAYER);
    client1->player->status = EGG;
    head->next = client1;
    game->player = head->player;
    game->player->next = client1->player;

    cmd_eject(head, head, game);
    cr_assert_str_eq(head->write_buf[1], "edi 2\n");
}

// Fork
Test(cmd_fork, sets_forking_status_and_time)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(5, 5, N);
    client->player = player;

    cmd_fork(NULL, client, game);

    cr_assert_eq(client->player->status, FORKING);
    cr_assert_neq(client->player->time_info.fork_start_time.tv_sec, 0);
}

Test(fork_by_player, creates_egg_and_sends_response)
{
    client_t *head = create_mock_client(0, GUI);
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(5, 5, N);
    team_t *team = create_mock_team("Team1", 1);
    client->player->team = team;
    game->player = client->player;
    game->player->next = player;

    int initial_slots = team->available_slots;

    fork_by_player(head, client, game);

    cr_assert_str_eq(client->write_buf[0], M_OK);
    cr_assert_eq(team->available_slots, initial_slots + 1);
    cr_assert_neq(game->given_id, 0);
}

// Forward
Test(cmd_forward, moves_player_forward)
{
    client_t *head = create_mock_client(0, GUI);
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(5, 5, N);
    client->player = player;

    cmd_forward(head, client, game);

    cr_assert_str_eq(client->write_buf[0], M_OK);
    cr_assert_eq(player->coordinate.x, 5);
    cr_assert_eq(player->coordinate.y, 4);

    player->orientation = E;
    cmd_forward(head, client, game);

    cr_assert_eq(player->coordinate.x, 6);
    cr_assert_eq(player->coordinate.y, 4);

    player->orientation = S;
    cmd_forward(head, client, game);
    cr_assert_eq(player->coordinate.x, 6);
    cr_assert_eq(player->coordinate.y, 5);

    player->orientation = W;
    cmd_forward(head, client, game);
    cr_assert_eq(player->coordinate.x, 5);
    cr_assert_eq(player->coordinate.y, 5);
}

// Right
Test(cmd_right, turns_right_from_north)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, N);
    client->player = player;

    cmd_right(NULL, client, game);

    cr_assert_eq(client->player->orientation, E);
}

Test(cmd_right, turns_right_from_east)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, E);
    client->player = player;

    cmd_right(NULL, client, game);

    cr_assert_eq(client->player->orientation, S);
}

Test(cmd_right, turns_right_from_south)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, S);
    client->player = player;

    cmd_right(NULL, client, game);

    cr_assert_eq(client->player->orientation, W);
}

Test(cmd_right, turns_right_from_west)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, W);
    client->player = player;

    cmd_right(NULL, client, game);

    cr_assert_eq(client->player->orientation, N);
}

// Left
Test(cmd_left, turns_left_from_north)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, N);
    client->player = player;

    cmd_left(NULL, client, game);

    cr_assert_eq(client->player->orientation, W);
}

Test(cmd_left, turns_left_from_east)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, E);
    client->player = player;

    cmd_left(NULL, client, game);
    cr_assert_eq(client->player->orientation, N);
}

Test(cmd_left, turns_left_from_south)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, S);
    client->player = player;

    cmd_left(NULL, client, game);
    cr_assert_eq(client->player->orientation, E);
}

Test(cmd_left, turns_left_from_west)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    player_t *player = create_mock_player(9, 9, W);
    client->player = player;

    cmd_left(NULL, client, game);
    cr_assert_eq(client->player->orientation, S);
}

// Set object
Test(cmd_set_object_tests, setting_valid_resource_1)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("linemate", &cmd_set_object, "linemate", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.linemate = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.linemate, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_2)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("food", &cmd_set_object, "food", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.food = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.food, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_3)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("deraumere", &cmd_set_object, "deraumere", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.deraumere = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.deraumere, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_4)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("sibur", &cmd_set_object, "sibur", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.sibur = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.sibur, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_5)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("mendiane", &cmd_set_object, "mendiane", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.mendiane = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.mendiane, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_6)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("phiras", &cmd_set_object, "phiras", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.phiras = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.phiras, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_7)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("thystame", &cmd_set_object, "thystame", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.thystame = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.thystame, 0);

    free(node);
}

Test(cmd_set_object_tests, setting_valid_resource_invalid)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("none", &cmd_set_object, NULL, 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    cmd_set_object(NULL, client, game);
    cr_assert_str_eq(client->write_buf[0], M_KO);

    free(node);
}

// Take object
Test(cmd_take_object_tests, taking_valid_resource_1)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("linemate", &cmd_take_object, "linemate", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].linemate = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.linemate, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_valid_resource_2)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("food", &cmd_take_object, "food", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].food = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.food, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_valid_resource_3)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("deraumere", &cmd_take_object, "deraumere", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].deraumere = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.deraumere, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_valid_resource_4)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("sibur", &cmd_take_object, "sibur", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].sibur = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.sibur, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_valid_resource_5)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("mendiane", &cmd_take_object, "mendiane", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].mendiane = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.mendiane, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_valid_resource_6)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("phiras", &cmd_take_object, "phiras", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].phiras = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.phiras, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_valid_resource_7)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("thystame", &cmd_take_object, "thystame", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].thystame = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_eq(client->player->inventory.thystame, 1);

    free(node);
}

Test(cmd_take_object_tests, taking_invalid_resource)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("none", &cmd_take_object, NULL, 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    cmd_take_object(NULL, client, game);
    cr_assert_str_eq(client->write_buf[0], M_KO);

    free(node);
}

// inventory
Test(cmd_inventory_tests, check_inventory)
{
    client_t *client = create_mock_client(1, PLAYER);
    game_t *game = create_mock_game(10, 10);
    game->map = create_map(10, 10);
    command_t *command = create_mock_command("inventory", &cmd_inventory, "inventory", 1);
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->command = *command;
    node->next = NULL;
    client->queue.head = node;
    client->queue.tail = node;
    client->queue.size = 1;
    client->player->inventory.food = 3;
    client->player->inventory.linemate = 2;
    client->player->inventory.deraumere = 4;
    client->player->inventory.sibur = 0;
    client->player->inventory.mendiane = 1;
    client->player->inventory.phiras = 1;
    client->player->inventory.thystame = 1;
    cmd_inventory(NULL, client, game);

    char buffer[BUFFER_SIZE];
    sprintf(buffer, INVENTORY_PATTERN,
            client->player->inventory.food * FOOD_TIME_LIMIT,
            client->player->inventory.linemate, client->player->inventory.deraumere,
            client->player->inventory.sibur, client->player->inventory.mendiane,
            client->player->inventory.phiras, client->player->inventory.thystame);
    cr_assert_str_eq(client->write_buf[0], buffer);
    free(node);
}

// get_resources_on_tile
Test(tile_resources_tests, check_get_tile_resources)
{
    team_t *team = NULL;
    map_t *map = create_map(10, 10);
    player_t *player = create_mock_player(5, 5, N);
    create_team(&team, "team1", 1);
    player->team = team;
    map->tile[5][5].food = 1;
    map->tile[5][5].linemate = 2;
    player->coordinate.x = 5;
    player->coordinate.y = 5;
    player->status = ALIVE;

    char *resources = get_tile_resources(player, map, 5, 5);
    cr_assert_str_eq(resources, "player_team1 food linemate linemate");
    free(resources);
}

// look
Test(cmd_functions_tests, check_cmd_look_up)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *client = create_mock_client(1, PLAYER);
    map_t *map = create_map(10, 10);
    create_team(&team, "team1", 1);
    game->map = map;
    game->map->tile[5][5].food = 1;
    game->map->tile[5][5].linemate = 2;

    client->player->coordinate.x = 5;
    client->player->coordinate.y = 5;
    client->player->level = 1;
    client->player->status = ALIVE;
    client->player->orientation = N;
    client->player->team = team;
    game->player = client->player;
    cmd_look(client, client, game);
    cr_assert_str_eq(client->write_buf[0], "[player_team1 food linemate linemate,food deraumere deraumere,phiras,sibur]\n");
}

Test(cmd_functions_tests, check_cmd_look_down)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *client = create_mock_client(1, PLAYER);
    map_t *map = create_map(10, 10);
    create_team(&team, "team1", 1);
    game->map = map;
    game->map->tile[5][5].food = 1;
    game->map->tile[5][5].linemate = 2;

    client->player->coordinate.x = 5;
    client->player->coordinate.y = 5;
    client->player->level = 1;
    client->player->status = ALIVE;
    client->player->orientation = S;
    client->player->team = team;
    game->player = client->player;
    cmd_look(client, client, game);
    cr_assert_str_eq(client->write_buf[0], "[player_team1 food linemate linemate,food,,mendiane]\n");
}

Test(cmd_functions_tests, check_cmd_look_right)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *client = create_mock_client(1, PLAYER);
    map_t *map = create_map(10, 10);
    create_team(&team, "team1", 1);
    game->map = map;
    game->map->tile[5][5].food = 1;
    game->map->tile[5][5].linemate = 2;

    client->player->coordinate.x = 5;
    client->player->coordinate.y = 5;
    client->player->level = 1;
    client->player->status = ALIVE;
    client->player->orientation = E;
    client->player->team = team;
    game->player = client->player;
    cmd_look(client, client, game);
    cr_assert_str_eq(client->write_buf[0], "[player_team1 food linemate linemate,sibur,food linemate,food]\n");
}

Test(cmd_functions_tests, check_cmd_look_left)
{
    team_t *team = NULL;
    game_t *game = create_mock_game(10, 10);
    client_t *client = create_mock_client(1, PLAYER);
    map_t *map = create_map(10, 10);
    create_team(&team, "team1", 1);
    game->map = map;
    game->map->tile[5][5].food = 1;
    game->map->tile[5][5].linemate = 2;

    client->player->coordinate.x = 5;
    client->player->coordinate.y = 5;
    client->player->level = 1;
    client->player->status = ALIVE;
    client->player->orientation = W;
    client->player->team = team;
    game->player = client->player;
    cmd_look(client, client, game);
    cr_assert_str_eq(client->write_buf[0], "[player_team1 food linemate linemate,mendiane,food,food deraumere deraumere]\n");
}

Test(cmd_functions_tests, check_cmd_incantation_valid)
{
    client_t *head = create_mock_client(1, GUI);
    client_t *client = create_mock_client(2, PLAYER);
    game_t *game = create_mock_game(10, 10);
    map_t *map = create_map(10, 10);
    head->next = client;

    client->player->coordinate.x = 0;
    client->player->coordinate.y = 0;
    client->player->level = 1;
    client->player->status = ALIVE;
    game->map = map;
    game->player = client->player;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].linemate = 1;
    cmd_incantation(head, client, game);
    cr_assert_eq(0, 0);
}

Test(cmd_functions_tests, check_cmd_incantation_invalid)
{
    client_t *head = create_mock_client(1, GUI);
    client_t *client = create_mock_client(2, PLAYER);
    game_t *game = create_mock_game(10, 10);
    map_t *map = create_map(10, 10);
    head->next = client;

    client->player->coordinate.x = 0;
    client->player->coordinate.y = 0;
    client->player->level = 1;
    client->player->status = ALIVE;
    game->map = map;
    game->player = client->player;
    game->map->tile[client->player->coordinate.x][client->player->coordinate.y].linemate = 0;
    cmd_incantation(head, client, game);
    cr_assert_str_eq(client->write_buf[0], M_KO);
    cr_assert_eq(client->player->status, ALIVE);
}
