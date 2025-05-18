/*
** EPITECH PROJECT, 2023
** tools.c
** File description:
** tools
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "management.h"
#include "network.h"
#include "tools.h"
#include "game.h"

void add_response(client_t * const client, const char * const message)
{
    char **new_buf = NULL;
    int size = 0;

    if (!client)
        return;
    if (client->write_buf)
        while (client->write_buf[size])
            size++;
    new_buf = realloc(client->write_buf, (size + 2) * sizeof(char *));
    CERROR(new_buf == NULL, "realloc");
    new_buf[size] = strdup(message);
    new_buf[size + 1] = NULL;
    client->write_buf = new_buf;
}

int *get_resource_counts(const map_t * const map, const int x, const int y)
{
    static int resource_counts[R_NB_RESOURCES];

    resource_counts[R_FOOD] = map->tile[x][y].food;
    resource_counts[R_LINEMATE] = map->tile[x][y].linemate;
    resource_counts[R_DERAUMERE] = map->tile[x][y].deraumere;
    resource_counts[R_SIBUR] = map->tile[x][y].sibur;
    resource_counts[R_MENDIANE] = map->tile[x][y].mendiane;
    resource_counts[R_PHIRAS] = map->tile[x][y].phiras;
    resource_counts[R_THYSTAME] = map->tile[x][y].thystame;
    return resource_counts;
}

int get_flag(const char * const * const av, const char * const flag)
{
    for (int i = 1; av[i]; ++i)
        if (!strcmp(av[i], flag) && av[i + 1] && atoi(av[i + 1]) > 0)
            return atoi(av[i + 1]);
    PERROR_FLAG(flag);
}

char **my_str_to_array(const char * const str, const char * const delim)
{
    char **array = NULL;
    int nb_words = 0;

    for (int i = 0; str[i];) {
        for (; strchr(delim, str[i]) && str[i]; i++);
        if (!str[i])
            break;
        nb_words++;
        int j = i;
        for (; !strchr(delim, str[j]) && str[j]; j++);
        array = realloc(array, sizeof(*array) * (nb_words + 1));
        array[nb_words - 1] = strndup(&str[i], j - i);
        array[nb_words] = NULL;
        i = j;
    }
    return array;
}

void my_free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
