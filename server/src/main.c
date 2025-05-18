/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "server.h"
#include "tools.h"

static int check_usage(const int ac, const char * const * const av)
{
    if (ac == 2 && !strcmp(av[1], "-help")) {
        printf(USAGE);
        exit(SUCCESS);
    }
    return SUCCESS;
}

int main(const int ac, const char * const * const av)
{
    return !check_usage(ac, av) ? server(av) : ERROR;
}
