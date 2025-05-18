/*
** EPITECH PROJECT, 2023
** player_incantation.c
** File description:
** player_incantation
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "game.h"

void incantation_failed(client_t * const head, client_t * const client)
{
    char buffer[BUFFER_SIZE];

    for (client_t *tmp = head; tmp; tmp = tmp->next)
        if (tmp->player && IS_SAME_COORD(tmp->player->coordinate,
        client->player->coordinate) && tmp->player->level >=
        client->player->level && (tmp->player->status == MASTER_INCANTATING ||
        tmp->player->status == INCANTATING)) {
            sprintf(buffer, PIE_PATTERN,
            tmp->player->coordinate.x, tmp->player->coordinate.y,
            INCANTATION_FAILED);
            add_response(get_gui(head), buffer);
            add_response(tmp, M_KO);
            tmp->player->status = ALIVE;
        }
}

void incantation_success(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    char buffer[BUFFER_SIZE];
    const int *actual_rule = INCANTATION_RULES[client->player->level - 1];

    remove_resources_on_tile(&game->map->tile
    [client->player->coordinate.x][client->player->coordinate.y], actual_rule);
    for (client_t *tmp = head; tmp; tmp = tmp->next)
        if (tmp->player && IS_SAME_COORD(tmp->player->coordinate,
        client->player->coordinate) && (tmp->player->status == MASTER_INCANTATING ||
        tmp->player->status == INCANTATING)) {
            tmp->player->time_info.incantation_start_time.tv_sec = 0;
            tmp->player->time_info.incantation_start_time.tv_nsec = 0;
            tmp->player->level++;
            sprintf(buffer, PIE_PATTERN,
            tmp->player->coordinate.x, tmp->player->coordinate.y,
            INCANTATION_SUCCESS);
            add_response(get_gui(head), buffer);
            sprintf(buffer, "Current level: %d\n", tmp->player->level);
            add_response(tmp, buffer);
            tmp->player->status = ALIVE;
        }
}

static char *start_incantation(U client_t *head, U player_t *player)
{
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    CERROR(buffer == NULL, "malloc");
    snprintf(buffer, BUFFER_SIZE, PIC_PATTERN, player->coordinate.x,
    player->coordinate.y, player->level, player->id);

    for (client_t *tmp = head; tmp; tmp = tmp->next)
        if (tmp->player && IS_SAME_COORD(tmp->player->coordinate,
        player->coordinate) && tmp->player->level >= player->level) {
            tmp->player->id != player->id ? snprintf(buffer + strlen(buffer),
            BUFFER_SIZE - strlen(buffer), " %d", tmp->player->id) : 0;
            tmp->player->time_info.command_wait_time =
            player->time_info.command_wait_time;
            clock_gettime(1, &tmp->player->time_info.incantation_start_time);
            tmp->player->status = INCANTATING;
            add_response(tmp, "Elevation underway\n");
        }
    snprintf(buffer + strlen(buffer),
    BUFFER_SIZE - strlen(buffer), "\n");
    return buffer;
}

void cmd_incantation(U client_t * const head,
U client_t * const client, U game_t * const game)
{
    if (is_incantation_valid(game, client->player)) {
        char *buffer = start_incantation(head, client->player);
        client->player->status = MASTER_INCANTATING;
        add_response(get_gui(head), buffer);
        return (void)free(buffer);
    }
    add_response(client, M_KO);
}
