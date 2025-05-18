/*
** EPITECH PROJECT, 2023
** CheckArgs.cpp
** File description:
** CheckArgs
*/

#include <iostream>
#include <string>

static const int ERROR = 84;
static const int SUCCESS = 0;
static const char USAGE[] = "USAGE: ./zappy_gui -p port -h machine\n"
"\tport\tis the port number\n"
"\tmachine\tis the name of the machine; localhost by default";

void check_help_argument(const int ac, char *av[]) {
    if (ac == 2 && std::string(av[1]) == "-help") {
        std::cout << USAGE << std::endl;
        exit(SUCCESS);
    }
}

int check_flags(int ac, char *av[])
{
    if (ac < 3 || ac == 4) {
        std::cerr << "Error: Invalid number of command line arguments!" << std::endl;
        return ERROR;
    }
    if (ac == 5) {
        if (std::string(av[1]) != "-p" || std::string(av[3]) != "-h") {
            std::cout << "Error: Invalid command line arguments" << std::endl;
            return ERROR;
        }
    }
    if (ac == 3) {
        if (std::string(av[1]) != "-p") {
            std::cout << "Error: Invalid command line arguments" << std::endl;
            return ERROR;
        }
    }
    return SUCCESS;
}

int check_port_validity(char *av[])
{
    try {
        int port = std::stoi(av[2]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Error: Invalid port number" << std::endl;
            return ERROR;
        }
    } catch (std::invalid_argument const &e) {
        std::cerr << "Error: Invalid port number";
        return ERROR;
    }
    return SUCCESS;
}

int checkArgs(const int ac, char *av[])
{
    check_help_argument(ac, av);
    return check_flags(ac, av) || check_port_validity(av) ? ERROR : SUCCESS;
}
