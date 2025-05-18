/*
** EPITECH PROJECT, 2023
** command_execution.c
** File description:
** command_execution
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "my_time.h"
#include "game.h"

static bool is_time_to_execute_command(client_t * const client,
const game_t * const game)
{
    struct timespec current_time;
    clock_gettime(1, &current_time);
    command_t command = get_head(&client->queue);
    double elapsed_time =
    GET_ELAPSED_TIME(client->player->time_info.command_start_time);

    if (client->player->time_info.command_start_time.tv_sec == 0) {
        client->player->time_info.command_wait_time = command.waiting_time;
        client->player->time_info.command_start_time = current_time;
        return false;
    }
    if (elapsed_time >= client->player->
    time_info.command_wait_time / game->freq) {
        client->player->time_info.command_start_time.tv_sec = 0;
        return true;
    }
    return false;
}

static void execute_gui(client_t * const head, client_t * const client,
game_t * const game, command_t command)
{
    if (command.cmd_function != NULL)
        command.cmd_function(head, client, game);
    dequeue(&client->queue);
}

static void execute_player(client_t * const head, client_t * const client,
game_t * const game, command_t command)
{
    if (!strcmp(command.name, INCANTATION)) {
        command.cmd_function(head, client, game);
        client->player->time_info.command_wait_time = command.waiting_time;
        dequeue(&client->queue);
    } else if (!command.cmd_function)
        dequeue(&client->queue);
    else if (client->status == PLAYER && client->player->status != DEAD &&
    is_time_to_execute_command(client, game)) {
        command.cmd_function(head, client, game);
        dequeue(&client->queue);
    }
}

static void execute_command(client_t * const head,
client_t * const client, game_t * const game)
{
    command_t command = get_head(&client->queue);

    if (client->status == GUI)
        execute_gui(head, client, game, command);
    else
        execute_player(head, client, game, command);
}

void handle_execution(const network_t * const network, game_t * const game)
{
    for (client_t *tmp = network->client; tmp; tmp = tmp->next)
        if ((tmp->status == GUI && tmp->queue.size > 0) ||
        (tmp->queue.size > 0 && tmp->player->status != INCANTATING &&
        tmp->player->status != MASTER_INCANTATING))
            execute_command(network->client, tmp, game);
}
