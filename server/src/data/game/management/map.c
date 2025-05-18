/*
** EPITECH PROJECT, 2023
** map.c
** File description:
** map
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "management.h"
#include "tools.h"
#include "game.h"

bool compare_tile(const game_t * const game,
const map_t * const tmp, const int x, const int y)
{
    char *tmp1 = get_tile_resources(game->player, tmp, x, y);
    char *tmp2 = get_tile_resources(game->player, game->map, x, y);
    bool are_equal = strcmp(tmp1, tmp2) == 0;

    free(tmp1);
    free(tmp2);
    return are_equal;
}

map_t *copy_map(const map_t *original)
{
    map_t *copy = malloc(sizeof(map_t));
    CERROR(copy == NULL, "malloc");

    copy->width = original->width;
    copy->height = original->height;
    copy->time_spread = original->time_spread;
    copy->tile = malloc(copy->width * sizeof(resource_t *));
    CERROR(copy->tile == NULL, "malloc");

    for (int i = 0; i < copy->width; ++i) {
        copy->tile[i] = malloc(copy->height * sizeof(resource_t));
        CERROR(copy->tile[i] == NULL, "malloc");
        for (int j = 0; j < copy->height; ++j)
            copy->tile[i][j] = original->tile[i][j];
    }
    return copy;
}

coordinate_t give_map_coordinate(const int width, const int height)
{
    coordinate_t coordinates;

    coordinates.x = rand() % width;
    coordinates.y = rand() % height;
    return coordinates;
}

map_t *create_map(const int width, const int height)
{
    map_t *map = malloc(sizeof(map_t));
    CERROR(map == NULL, "malloc");

    map->width = width;
    map->height = height;
    if (map->width <= 1 && map->height <= 1)
        PERROR("Invalid map size\n");
    map->tile = malloc(map->width * sizeof(resource_t *));
    CERROR(map->tile == NULL, "malloc");
    for (int i = 0; i < map->width; i++)
        map->tile[i] = calloc(map->height, sizeof(resource_t));
    spread_resources(map);
    clock_gettime(1, &map->time_spread);
    return map;
}
