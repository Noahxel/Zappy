/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Comunicator
*/

#ifndef COMUNICATOR_HPP_
#define COMUNICATOR_HPP_
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include "MyCppLib.hpp"
#include "AElem.hpp"
#define WELCOME_BG_PATH "gui/assets/welcomeBG.png"

namespace GUI {
    class Comunicator {
        public:
            Comunicator(int, char **, std::shared_ptr<sf::RenderWindow>);
            ~Comunicator();
            void ConnectToServer(int, char **);
            void WriteToServer(std::string);
            void ResetFd();
            std::vector<std::string> ReadFromServer();
            void WaitForServer(std::string);

        private:
            int _serverFd;
            fd_set _rfds;
            std::string _extraString;
            std::unique_ptr<AElem> _welcomeBg;
            sf::Event _gameEvents;
    };
}

#endif /* !COMUNICATOR_HPP_ */
