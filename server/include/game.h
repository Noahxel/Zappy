/*
** EPITECH PROJECT, 2023
** game.h
** File description:
** game
*/

#pragma once

#include <time.h>
#include <stddef.h>
#include <stdbool.h>

#include "my_time.h"

static const int MAX_LEVEL = 8;
static const int NB_PLAYERS_FOR_WINNING = 6;

typedef enum {
    ALIVE,
    DEAD,
    INCANTATING,
    MASTER_INCANTATING,
    FORKING,
    EGG,
    UNAFFECTED
} player_status_e;

typedef enum {
    N = 1,
    E = 2,
    S = 3,
    W = 4,
    LEN_ORIENTATION = 4
} orientation_e;

typedef struct resource_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} resource_t;

typedef struct coordinate_s {
    int x;
    int y;
} coordinate_t;

typedef struct map_s {
    resource_t **tile;
    int width;
    int height;
    struct timespec time_spread;
} map_t;

typedef struct team_s {
    char *team_name;
    int available_slots;
    struct team_s *next;
} team_t;

typedef struct player_s {
    int id;
    int level;
    time_info_t time_info;
    team_t *team;
    resource_t inventory;
    coordinate_t coordinate;
    orientation_e orientation;
    player_status_e status;
    struct player_s *next;
} player_t;

typedef struct game_s {
    int freq;
    int given_id;
    map_t *map;
    team_t *team;
    player_t *player;
} game_t;
