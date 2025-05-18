/*
** EPITECH PROJECT, 2023
** destroy.h
** File description:
** destroy
*/

#pragma once

#include <stdlib.h>

typedef struct game_s game_t;
typedef struct map_s map_t;

void destroy_game(game_t game);
void destroy_map(map_t * const map);
