/*
** EPITECH PROJECT, 2023
** command.c
** File description:
** command
*/

#include <stdio.h>
#include <string.h>

#include "management.h"
#include "network.h"
#include "game.h"

static int what_cmd(char * const command, const command_t * const command_list)
{
    int cmd_idx = FAIL;

    for (int i = 0; command_list[i].name; i++)
        if (!strncmp(command, command_list[i].name,
        strlen(command_list[i].name)))
            return i;
    if (cmd_idx == FAIL)
        return FAIL;
    return cmd_idx;
}

static command_t add_optional_arg_to_command(command_t command,
char * const cmd)
{
    for (int i = 0; PLAYER_CMD_WITH_OPTIONAL_ARGS[i]; i++)
        if (!strncmp(PLAYER_CMD_WITH_OPTIONAL_ARGS[i], cmd,
        strlen(PLAYER_CMD_WITH_OPTIONAL_ARGS[i]))) {
            U char *cmd_name = strtok(cmd, " ");
            char *cmd_arg = strtok(NULL, "");
            command.arg = strdup(cmd_arg);
        }
    for (int i = 0; GUI_CMD_WITH_OPTIONAL_ARGS[i]; i++)
        if (!strncmp(GUI_CMD_WITH_OPTIONAL_ARGS[i], cmd, 3))
            command.arg = strdup(cmd);
    return command;
}

static void handle_queue(client_t * const client,
const command_t * const command_list, char * const cmd)
{
    const int idx = what_cmd(cmd, command_list);

    if (idx == FAIL) {
        command_t unknow_cmd = {NULL, NULL, NULL, 0};
        if (IS_QUEUE_MAX_SIZE(client) == false)
            enqueue(&client->queue, unknow_cmd);
    } else {
        command_t command = command_list[idx];
        command = add_optional_arg_to_command(command, cmd);
        if (IS_QUEUE_MAX_SIZE(client) == false)
            enqueue(&client->queue, command);
    }
}

void handle_command(const network_t * const network)
{
    for (client_t *tmp = network->client; tmp; tmp = tmp->next) {
        if (!tmp->commands)
            continue;
        for (int i = 0; tmp->commands[i]; i++) {
            tmp->status == PLAYER && (tmp->player->status != MASTER_INCANTATING
            && tmp->player->status != INCANTATING) ?
            handle_queue(tmp, PLAYER_CMD, tmp->commands[i]) : 0;
            tmp->status == GUI ?
            handle_queue(tmp, GUI_CMD, tmp->commands[i]) : 0;
        }
        if (tmp->commands) {
            my_free_array(tmp->commands);
            tmp->commands = NULL;
        }
    }
}
