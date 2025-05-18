/*
** EPITECH PROJECT, 2023
** command.h
** File description:
** command
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

#define U __attribute__((unused))
#define QUEUE_MAX_SIZE 10

typedef struct resource_s resource_t;
typedef struct client_s client_t;
typedef struct game_s game_t;

typedef struct command_s {
    const char *name;
    void (*cmd_function)(U client_t * const,
    U client_t * const , U game_t * const);
    char *arg;
    int waiting_time;
} command_t;

typedef struct node_s {
    command_t command;
    struct node_s* next;
} node_t;

typedef struct queue_s {
    node_t *head;
    node_t *tail;
    int size;
} queue_t;

void cmd_forward(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_right(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_left(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_look(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_inventory(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_broadcast_text(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_connect_nbr(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_fork(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_eject(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_take_object(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_set_object(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_incantation(U client_t * const head,
U client_t * const client, U game_t * const game);

static const char INVENTORY_PATTERN[] =
"[food %d, linemate %d, deraumere %d, sibur %d,"
" mendiane %d, phiras %d, thystame %d]\n";

static const command_t PLAYER_CMD[] =
{
    {"Forward", cmd_forward, NULL, 7},
    {"Right", cmd_right, NULL, 7},
    {"Left", cmd_left, NULL, 7},
    {"Look", cmd_look, NULL, 7},
    {"Inventory", cmd_inventory, NULL, 1},
    {"Broadcast", cmd_broadcast_text, NULL, 7},
    {"Connect_nbr", cmd_connect_nbr, NULL, 0},
    {"Fork", cmd_fork, NULL, 42},
    {"Eject", cmd_eject, NULL, 7},
    {"Take", cmd_take_object, NULL, 7},
    {"Set", cmd_set_object, NULL, 7},
    {"Incantation", cmd_incantation, NULL, 300},
    {NULL, NULL, NULL, 0}
};

U static const char *PLAYER_CMD_WITH_OPTIONAL_ARGS[] =
{
    "Broadcast", "Take", "Set", NULL
};

void cmd_msz(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_bct(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_mct(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_tna(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_ppo(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_plv(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_pin(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_pwa(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_sgt(U client_t * const head,
U client_t * const client, U game_t * const game);
void cmd_sst(U client_t * const head,
U client_t * const client, U game_t * const game);

static const char MSZ_PATTERN[] = "msz %d %d\n";
static const char BCT_PATTERN[] = "bct %d %d %d %d %d %d %d %d %d\n";
static const char TNA_PATTERN[] = "tna %s\n";
static const char PNW_PATTERN[] = "pnw #%d %d %d %d %d %s\n";
static const char PPO_PATTERN[] = "ppo %d %d %d %d\n";
static const char PLV_PATTERN[] = "plv %d %d\n";
static const char PIN_PATTERN[] = "pin %d %d %d %d %d %d %d %d %d %d\n";
static const char PEX_PATTERN[] = "pex %d\n";
static const char PBC_PATTERN[] = "pbc %d %s\n";
static const char PIC_PATTERN[] = "pic %d %d %d %d";
static const char PIE_PATTERN[] = "pie %d %d %d\n";
static const char PDR_PATTERN[] = "pdr %d %d\n";
static const char PGT_PATTERN[] = "pgt %d %d\n";
static const char PDI_PATTERN[] = "pdi %d\n";
static const char ENW_PATTERN[] = "enw %d %d %d %d\n";
static const char EBO_PATTERN[] = "ebo %d\n";
static const char EDI_PATTERN[] = "edi %d\n";
static const char SEG_PATTERN[] = "seg %s\n";
static const char SGT_PATTERN[] = "sgt %d\n";

U static const char *GUI_CMD_WITH_OPTIONAL_ARGS[] =
{
    "bct", "ppo", "plv", "pin", NULL
};

static const command_t GUI_CMD[] =
{
    {"msz", cmd_msz, NULL, 0},
    {"bct", cmd_bct, NULL, 0},
    {"mct", cmd_mct, NULL, 0},
    {"tna", cmd_tna, NULL, 0},
    {"ppo", cmd_ppo, NULL, 0},
    {"plv", cmd_plv, NULL, 0},
    {"pin", cmd_pin, NULL, 0},
    {"pwa", cmd_pwa, NULL, 0},
    {"sgt", cmd_sgt, NULL, 0},
    {"sst", cmd_sst, NULL, 0},
    {NULL, NULL, NULL, 0}
};
