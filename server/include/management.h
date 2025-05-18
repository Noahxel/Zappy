/*
** EPITECH PROJECT, 2023
** management.h
** File description:
** management
*/

#pragma once

#include <stdbool.h>
#include "tools.h"
#include "command.h"

typedef struct coordinate_s coordinate_t;
typedef struct resource_s resource_t;
typedef struct network_s network_t;
typedef struct command_s command_t;
typedef struct client_s client_t;
typedef struct player_s player_t;
typedef struct game_s game_t;
typedef struct team_s team_t;
typedef struct map_s map_t;

#define PI 3.14159265358979323846
#define M_DISCONNECTION(fd) ({ printf(DISCONNECTION_MESS, fd); })
#define M_WELCOME(fd) (dprintf(fd, WELCOME_MESS))
#define M_WINNER(fd, mess) (dprintf(fd, mess))
#define IS_SAME_COORD(x_crd, y_crd) (x_crd.x == y_crd.x && x_crd.y == y_crd.y)
#define IS_QUEUE_MAX_SIZE(client) ((client)->queue.size >= \
QUEUE_MAX_SIZE && (client)->status == PLAYER)

static const int INCANTATION_SUCCESS = 0;
static const int INCANTATION_FAILED = 1;
static const char AFFECT_MESS[] = "client [%d] affected to player id [%d]\n";
static const char DISCONNECTION_MESS[] = "User disconnect with fd [%d].\n";
static const char ELEVATION_UNDERWAY_MESS[] = "Elevation underway\n";
static const char WELCOME_MESS[] = "WELCOME\n";
static const char INCANTATION[] = "Incantation";
static const char M_DEAD[] = "dead\n";
static const char M_OK[] = "ok\n";
static const char M_KO[] = "ko\n";

static const char * const RESOURCES[] =
{
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
};

static const double DENSITY[] =
{
    0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05
};

static const int INCANTATION_RULES[7][8] =
{
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}
};

typedef enum {
    LEVEL,
    NB_PLAYERS,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} incantation_pattern_e;

typedef enum {
    R_FOOD,
    R_LINEMATE,
    R_DERAUMERE,
    R_SIBUR,
    R_MENDIANE,
    R_PHIRAS,
    R_THYSTAME,
    R_NONE,
    R_NB_RESOURCES = 7
} resource_type_e;


void assignment_to_team(client_t * const gui,
client_t * const client, game_t * const game);
void assignment_to_gui(client_t * const client, bool * const is_there_gui);

bool is_incantation_valid(const game_t * const game, player_t * const player);
void incantation_success(U client_t * const head,
U client_t * const client, U game_t * const game);
void incantation_failed(client_t * const head, client_t * const client);

void fork_by_player
(client_t * const head, client_t * const client, game_t * const game);

map_t *copy_map(const map_t *original);
map_t *create_map(const int width, const int height);
coordinate_t give_map_coordinate(const int width, const int height);
bool compare_tile(const game_t * const game,
const map_t * const tmp, const int x, const int y);

char *get_tile_resources(player_t * const head,
const map_t * const map, const int x, const int y);
void spread_resources(map_t * const map);
void remove_resources_on_tile(resource_t * const tile,
const int * const actual_rule);
void ensure_min_resources(map_t * const map);

void create_player(player_t ** const head,
team_t * const team, const map_t * const map, const int id);
void create_egg(player_t ** const head,
team_t * const team, const map_t * const map, const int id);
void remove_player(player_t ** const head, const player_t * const player);

resource_t create_inventory(void);

void create_team
(team_t ** const head, char * const team_name, const int max_slots);
void check_duplicate_teams(team_t *teams, const char * const team_name);
int nb_teams(const char * const *av);

void create_client(client_t ** const head, int new_fd);
void disconnect_client(client_t ** const head, client_t * const client);
client_t *get_gui(client_t * const head);

void reset_socket_fd(network_t * const network);

void enqueue(queue_t * const queue, const command_t command);
void dequeue(queue_t * const queue);
command_t get_head(queue_t * const queue);
void free_queue(queue_t * const queue);
