/*
** EPITECH PROJECT, 2023
** project.h
** File description:
** project.h
*/

#pragma once

#define M_SERVER_START(fd) ({ printf(START_MESS, fd); })
#define M_SERVER_CLOSE ({ printf(CLOSE_MESS); 0; })

static const char START_MESS[] = "Server start with fd [%d].\n";
static const char CLOSE_MESS[] = "Server close.\r\n";
static const int TIMEOUT_TIME = 10;

static const char USAGE[] =
"USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... "
"-c clientsNb -f freq\n"
"\tport\t\tis the port number\n"
"\twidth\t\tis the width of the world\n"
"\theight\t\tis the height of the world\n"
"\tnameX\t\tis the name of the team X\n"
"\tclientsNb\tis the number of authorized clients per team\n"
"\tfreq\t\tis the reciprocal of time unit for execution of actions\n";

int server(const char * const *av);
