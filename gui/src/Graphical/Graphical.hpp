/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Graphical
*/

#ifndef GRAPHICAL_HPP_
#define GRAPHICAL_HPP_
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "MyCppLib.hpp"
#include "Comunicator.hpp"
#include "World.hpp"
#include "PlayerInterface.hpp"
#define GOODBY_BG_PATH "gui/assets/goodbyBG.png"

namespace GUI {
    class Graphical {
        public:
            Graphical(int ac, char **av);
            ~Graphical();
            void InitGUI();
            void RunGUI();
            void GetDataFromServer();
            void RefreshWorld();
            void RefreshPlayerPos();
            void handleGameEvents();

        private:
            std::shared_ptr<sf::RenderWindow> _gameWindow;
            Comunicator _server;
            World _world;
            PlayerInterface _pi;
            sf::Event _gameEvents;
            sf::Vector2f _mouseLastPos;
            bool _isMousePressed;
            sf::Clock _mouseClock;
            sf::Clock _refreshInterfaceClock;
            bool _haveToRmPlayerFromInterface;
            std::unique_ptr<AElem> _goodbyBG;
            sf::Text winnersText;
    };
}

#endif /* !GRAPHICAL_HPP_ */
