/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Comunicator
*/

#include "Comunicator.hpp"

namespace GUI {
    Comunicator::Comunicator(int ac, char **av, std::shared_ptr<sf::RenderWindow> window)
    {
        std::string serverIP;
        int serverPort = atoi(av[2]);
        sockaddr_in serverAddress {};

        if (ac < 5)
            serverIP = "127.0.0.1";
        if (ac == 5) {
            if (strcmp(av[4], "localhost") == 0)
                serverIP = "127.0.0.1";
            else
                serverIP = av[4];
        }

        if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            throw std::runtime_error("Failed to create socket\n");
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(serverPort);
        if (inet_pton(AF_INET, serverIP.c_str(), &(serverAddress.sin_addr)) <= 0) {
            close(_serverFd);
            throw std::runtime_error("Invalid address/Address not supported\n");
        }

        sf::Texture bgTexture;
        if (!bgTexture.loadFromFile(WELCOME_BG_PATH))
            throw std::runtime_error("cant load bgTexture\n");
        _welcomeBg = std::make_unique<AElem>("welcomeBg", std::make_shared<sf::Texture>(bgTexture));

        while (connect(_serverFd, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
            while (window->pollEvent(_gameEvents)) {
                if (_gameEvents.type == sf::Event::Closed) {
                    window->close();
                    throw std::runtime_error("GUI closed\n");
                }
            }
            window->clear();
            window->draw(_welcomeBg->GetElemSprite());
            _welcomeBg->SetElemPos(sf::Vector2f(0, 0));
            window->display();
        }
    }

    Comunicator::~Comunicator()
    {
    }

    void Comunicator::ResetFd()
    {
        FD_ZERO(&_rfds);
        FD_SET(_serverFd, &_rfds);
    }

    void Comunicator::WriteToServer(std::string ask)
    {
        if (send(_serverFd, ask.c_str(), ask.size(), 0) < 0)
            throw std::runtime_error("send failed\n");
    }

    void Comunicator::WaitForServer(std::string waitinFor)
    {
        std::string receiverData;
        ssize_t bytes;
        char buffer[BUFSIZ];

        while (waitinFor != receiverData) {
            if ((bytes = recv(_serverFd, buffer, BUFSIZ - 1, 0)) <= 0) {
                throw std::runtime_error("server closed");
            }
            buffer[bytes] = '\0';
            receiverData += buffer;
        }
    }

    std::vector<std::string> Comunicator::ReadFromServer()
    {
        int max = _serverFd + 1;
        int bytes = 0;
        char response[BUFSIZ];
        std::vector<std::string> parsed;
        timeval timeout;

        timeout.tv_sec = 0;
        timeout.tv_usec = 100;

        memset(response, 0, BUFSIZ);
        ResetFd();
        if (select(max, &_rfds, NULL, NULL, &timeout) < 0)
            throw std::runtime_error("client select failed");
        if (FD_ISSET(_serverFd, &_rfds)) {
            if ((bytes = recv(_serverFd, response, BUFSIZ - 1, 0)) <= 0)
                throw std::runtime_error("server closed");
            response[bytes] = '\0';
            if (_extraString.size() > 0) {
                _extraString += response;
                parsed = MyCppLib::splitString(_extraString, '\n');
                _extraString.clear();
            } else
                parsed = MyCppLib::splitString(response, '\n');
            if (bytes >= BUFSIZ - 1) {
                std::vector<std::string> lastResponse = MyCppLib::splitString(parsed.back(), ' ');
                if (lastResponse.size() != 10 || !std::isdigit(lastResponse.back().back())) {
                    _extraString = parsed.back();
                    parsed.pop_back();
                }
            }
        }
        return (parsed);
    }
}