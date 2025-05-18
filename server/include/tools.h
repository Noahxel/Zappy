/*
** EPITECH PROJECT, 2023
** tools.h
** File description:
** tools
*/

#pragma once

typedef struct client_s client_t;
typedef struct map_s map_t;

#define BUFFER_SIZE 1024
#define PERROR_FLAG(e) fprintf(stderr, M_PERROR_FALG, e); exit(ERROR);
#define PERROR(e) fprintf(stderr, "Error: %s\n", e), exit(ERROR);
#define CERROR(iserror, e) ((iserror) ? (perror(e), exit(ERROR)) : 0)

static const int SUCCESS = 0;
static const int FAIL = -1;
static const int ERROR = 84;
static const char USLESS_DELIMITERS[] = "\r\t";
static const char M_PERROR_FALG[] = "Error: %s argument.\n";

char **my_str_to_array(const char * const str, const char * const d);
void my_free_array(char **array);
void add_response(client_t *client, const char * const message);
int get_flag(const char * const * const av, const char * const flag);
int *get_resource_counts(const map_t * const map, const int x, const int y);
