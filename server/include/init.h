/*
** EPITECH PROJECT, 2023
** init.h
** File description:
** init
*/

#pragma once

typedef struct game_s game_t;
typedef struct player_s player_t;
typedef struct team_s team_t;
typedef struct map_s map_t;

typedef struct network_s network_t;
typedef struct socket_s socket_t;

static const int DEFAULT_FREQUENCE = 100;

void init_game(const char * const * const av, game_t * const game);
team_t *init_teams(const char * const * const av, int nb_teams, int max_slots);
player_t *init_players
(const map_t * const map, team_t * const team, const int nb_clients_per_team);
int init_freq(const char * const * const av, const char *flag);

void init_network(const char * const *av, network_t * const network);
void init_server_socket(socket_t * const sock, const int port);
