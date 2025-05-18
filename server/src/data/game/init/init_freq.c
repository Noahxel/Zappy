/*
** EPITECH PROJECT, 2023
** init_freq.c
** File description:
** init_freq
*/

#include <string.h>
#include <stdlib.h>

#include "init.h"

int init_freq(const char * const *av, const char *flag)
{
    for (int i = 1; av[i]; ++i)
        if (!strcmp(av[i], flag) && av[i + 1] && atoi(av[i + 1]) > 0)
            return atoi(av[i + 1]);
    return DEFAULT_FREQUENCE;
}
