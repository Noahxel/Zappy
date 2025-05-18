/*
** EPITECH PROJECT, 2023
** events.h
** File description:
** events
*/

#pragma once

#include <sys/select.h>

typedef struct network_s network_t;
typedef struct client_s client_t;
typedef struct game_s game_t;

#define HANDLE_EVENTS ({ handle_events(game, network); 1; })

void handle_events(game_t * const game, network_t * const network);
void handle_new_connection_event(network_t * const network);
void handle_end_game(client_t * const head, const game_t * const game);
void handle_time_event(client_t * const head, game_t * const game);
void handle_read_event(network_t * const network);
void handle_assignment(network_t * const network, game_t * const game);
void handle_command(const network_t * const network);
void handle_execution
(const network_t * const network, const game_t * const game);
void handle_write_event(const network_t * const network);
void handle_status_event(network_t * const network, game_t * const game);
