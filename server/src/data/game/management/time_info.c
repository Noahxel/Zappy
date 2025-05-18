/*
** EPITECH PROJECT, 2023
** time_info.c
** File description:
** time_info
*/

#include <time.h>
#include "my_time.h"

void init_time_info(time_info_t *time_info)
{
    time_info->last_eat_cooldown.tv_sec = 0;
    time_info->last_eat_cooldown.tv_nsec = 0;
    time_info->command_start_time.tv_sec = 0;
    time_info->command_start_time.tv_nsec = 0;
    time_info->incantation_start_time.tv_sec = 0;
    time_info->incantation_start_time.tv_nsec = 0;
    time_info->fork_start_time.tv_sec = 0;
    time_info->fork_start_time.tv_nsec = 0;
    time_info->command_wait_time = 0;
}
