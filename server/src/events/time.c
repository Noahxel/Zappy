/*
** EPITECH PROJECT, 2023
** time.c
** File description:
** time
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "management.h"
#include "network.h"
#include "my_time.h"
#include "destroy.h"
#include "tools.h"
#include "game.h"

static void is_time_end_fork(client_t * const head,
client_t * const client, game_t * const game)
{
    double elapsed_time =
    GET_ELAPSED_TIME(client->player->time_info.fork_start_time);
    double fork_wait_time =
    client->player->time_info.command_wait_time / game->freq;

    if (elapsed_time >= fork_wait_time) {
        fork_by_player(head, client, game);
        client->player->time_info.fork_start_time.tv_sec = 0;
        client->player->time_info.fork_start_time.tv_nsec = 0;
        client->player->status = ALIVE;
    }
}

static void is_time_end_incantation(client_t * const head,
client_t * const client, game_t * const game)
{
    double elapsed_time =
    GET_ELAPSED_TIME(client->player->time_info.incantation_start_time);
    double incantation_wait_time =
    client->player->time_info.command_wait_time / game->freq;

    if (is_incantation_valid(game, client->player)) {
        if (elapsed_time >= incantation_wait_time) {
            incantation_success(head, client, game);
        }
    } else
        incantation_failed(head, client);
}

static void is_time_player_death(client_t * const client, const int freq)
{
   double elapsed_time =
   GET_ELAPSED_TIME(client->player->time_info.last_eat_cooldown);

   if (elapsed_time >= (double)FOOD_TIME_LIMIT / freq) {
       if (client->player->inventory.food == 0) {
           client->player->status = DEAD;
           add_response(client, M_DEAD);
       } else {
           client->player->inventory.food--;
           clock_gettime(1, &client->player->time_info.last_eat_cooldown);
       }
   }
}

static void is_time_spread_resources(client_t * const head,
const game_t * const game)
{
    const double elapsed_time = GET_ELAPSED_TIME(game->map->time_spread);
    map_t *tmp = copy_map(game->map);
    char buffer[BUFFER_SIZE];
    resource_t resource;

    if (elapsed_time < (double)SPAWN_TIME_LIMIT / game->freq)
        return (void)destroy_map(tmp);
    spread_resources(game->map);
    for (int x = 0; x < game->map->width; ++x)
        for (int y = 0; y < game->map->height; ++y) {
            compare_tile(game, tmp, x, y) == false ?
            resource = game->map->tile[x][y],
            sprintf(buffer, BCT_PATTERN, x, y, resource.food,
            resource.linemate, resource.deraumere, resource.sibur,
            resource.mendiane, resource.phiras, resource.thystame),
            add_response(get_gui(head), buffer) : 0;
        }
    destroy_map(tmp);
}

void handle_time_event(client_t * const head, game_t * const game)
{
    is_time_spread_resources(head, game);
    for (client_t *tmp = head; tmp; tmp = tmp->next) {
        if (tmp->player) {
            tmp->player->status == MASTER_INCANTATING ?
            is_time_end_incantation(head, tmp, game) : 0;
            tmp->player->status == FORKING ?
            is_time_end_fork(head, tmp, game) : 0;
            is_time_player_death(tmp, game->freq);
        }
    }
}
