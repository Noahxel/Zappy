/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerInterface
*/

#ifndef PLAYERINTERFACE_HPP_
#define PLAYERINTERFACE_HPP_

#include "AElem.hpp"
#include <cmath>
#define LEFT_TEXTURE_PATH "gui/assets/left.png"
#define RIGHT_TEXTURE_PATH "gui/assets/right.png"
#define LEVEL_ARRAY_PATH "gui/assets/lvlArr.png"
#define PLAYER_ASSETS_PATH "gui/assets/player/"
#define LEFT 0
#define RIGHT 1

#define TRANSPARENT 128
#define OPAQUE 255

namespace GUI{
    class PlayerInterface {
        public:
            PlayerInterface(std::shared_ptr<sf::RenderWindow> gameWindow);
            ~PlayerInterface();
            void displayPlayerInterface();
            void setTeamsInfos(std::map<std::string, std::shared_ptr<sf::Color>> teamsInfos);
            bool changeTeamSpec(sf::Vector2f mouseClick);
            void setPlayerLevel(std::vector<int> playerIds);
            std::string getDisplayedTeamName();

        protected:
        private:
            typedef struct team_s {
                sf::Text _teamName;
                sf::RectangleShape _teamColorRect;
                sf::Vector2f _teamColorRectPos;
                sf::Vector2f _teamColorRectSize;
                std::vector<int> teamPlayersIds;
            } team_t;

            sf::View _defaultView;
            std::shared_ptr<sf::RenderWindow> _gameWindow;
            std::vector<team_t> teams;
            int currentTeamId;

            std::vector<std::unique_ptr<AElem>> _leftRightButtons;
            std::map<std::string, std::shared_ptr<sf::Texture>> _playerTextures;
            std::vector<std::unique_ptr<AElem>> _playerHeads;

            std::unique_ptr<AElem> _playerLevelArray;
            sf::RectangleShape _interfaceBg;
            sf::Vector2f _interfaceBgPos;
            sf::Vector2f _interfaceBgSize;
            sf::Color _interfaceBgColor;
            sf::Font _font;
    };
}
#endif /* !PLAYERINTERFACE_HPP_ */
