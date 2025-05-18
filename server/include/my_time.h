/*
** EPITECH PROJECT, 2023
** time.h
** File description:
** time
*/

#pragma once

#define GET_ELAPSED_TIME(start_time) \
    ({ \
        struct timespec current_time; \
        clock_gettime(1, &current_time); \
        double elapsed_time = (current_time.tv_sec - (start_time).tv_sec) + \
        ((current_time.tv_nsec - (start_time).tv_nsec) / 1e9); \
        elapsed_time; \
    })

typedef struct time_info_s {
    struct timespec last_eat_cooldown;
    struct timespec command_start_time;
    struct timespec incantation_start_time;
    struct timespec fork_start_time;
    double command_wait_time;
} time_info_t;

static const int SPAWN_TIME_LIMIT = 20;
static const int FOOD_TIME_LIMIT = 126;

void init_time_info(time_info_t *time_info);
