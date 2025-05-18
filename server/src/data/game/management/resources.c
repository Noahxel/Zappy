/*
** EPITECH PROJECT, 2023
** resources.c
** File description:
** resources
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "tools.h"
#include "game.h"

void remove_resources_on_tile(resource_t * const tile,
const int * const actual_rule)
{
    tile->linemate -= actual_rule[LINEMATE];
    tile->linemate < 0 ? tile->linemate = 0 : 0;
    tile->deraumere -= actual_rule[DERAUMERE];
    tile->deraumere < 0 ? tile->deraumere = 0 : 0;
    tile->sibur -= actual_rule[SIBUR];
    tile->sibur < 0 ? tile->sibur = 0 : 0;
    tile->mendiane -= actual_rule[MENDIANE];
    tile->mendiane < 0 ? tile->mendiane = 0 : 0;
    tile->phiras -= actual_rule[PHIRAS];
    tile->phiras < 0 ? tile->phiras = 0 : 0;
    tile->thystame -= actual_rule[THYSTAME];
    tile->thystame < 0 ? tile->thystame = 0 : 0;
}

static int nb_resources_on_map(resource_t * const * const res, const int width,
const int height, const int k)
{
    int count = 0;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            k == 0 ? count += res[i][j].food :
            k == 1 ? count += res[i][j].linemate :
            k == 2 ? count += res[i][j].deraumere :
            k == 3 ? count += res[i][j].sibur :
            k == 4 ? count += res[i][j].mendiane :
            k == 5 ? count += res[i][j].phiras :
            k == 6 ? count += res[i][j].thystame : 0;
        }
    return count;
}

void ensure_min_resources(map_t * const map)
{
    for (int k = 0; k < 7; k++) {
        int res_count = nb_resources_on_map
        (map->tile, map->width, map->height, k);
        if (res_count == 0) {
            int i = rand() % map->width;
            int j = rand() % map->height;
            k == 0 ? map->tile[i][j].food++ :
            k == 1 ? map->tile[i][j].linemate++ :
            k == 2 ? map->tile[i][j].deraumere++ :
            k == 3 ? map->tile[i][j].sibur++ :
            k == 4 ? map->tile[i][j].mendiane++ :
            k == 5 ? map->tile[i][j].phiras++ :
            k == 6 ? map->tile[i][j].thystame++ : 0;
        }
    }
}

void spread_resources(map_t * const map)
{
    const int total_cells = map->width * map->height;

    for (int k = 0; k < 7; k++) {
        int res_count = nb_resources_on_map
        (map->tile, map->width, map->height, k);
        int res_required = total_cells * DENSITY[k] + 0.5 - res_count;
        if (res_required < 0) res_required = 0;
        for (int r = 0; r < res_required; r++) {
            int i = rand() % map->width;
            int j = rand() % map->height;
            k == 0 ? map->tile[i][j].food++ :
            k == 1 ? map->tile[i][j].linemate++ :
            k == 2 ? map->tile[i][j].deraumere++ :
            k == 3 ? map->tile[i][j].sibur++ :
            k == 4 ? map->tile[i][j].mendiane++ :
            k == 5 ? map->tile[i][j].phiras++ :
            k == 6 ? map->tile[i][j].thystame++ : 0;
        }
    } ensure_min_resources(map);
    clock_gettime(1, &map->time_spread);
}

char *get_tile_resources(player_t * const head,
const map_t * const map, const int x, const int y)
{
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    CERROR(buffer == NULL, "malloc");
    buffer[0] = '\0';

    for (player_t *tmp = head; tmp; tmp = tmp->next)
        if (tmp->coordinate.x == x && tmp->coordinate.y == y &&
        tmp->status != UNAFFECTED) {
            strcat(buffer, "player_");
            strcat(buffer, tmp->team->team_name);
            strcat(buffer, " ");
            break;
        }
    for (int i = 0; i < R_NB_RESOURCES; i++)
        for (int j = 0; j < get_resource_counts(map, x, y)[i]; j++) {
            strcat(buffer, RESOURCES[i]);
            strcat(buffer, " ");
        }
    if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == ' ')
        buffer[strlen(buffer) - 1] = '\0';
    return buffer;
}
