/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include "AElem.hpp"
#define PLAYER_ASSETS_PATH "gui/assets/player/"
#define INCANTATION_SOUND_PATH "gui/assets/incantationComplete.ogg"
#define N 1
#define E 2
#define S 3
#define W 4
#define BROADCAST_SIZE 100

namespace GUI {
    class Player {
        public:
            Player(int, std::vector<int>, int, std::string, std::shared_ptr<sf::Texture>);
            ~Player();
            void PlayerSetLevel(bool = false);
            sf::Sprite GetPlayerSprite();
            void SetPlayerArrayCoos(sf::Vector2f);
            sf::Vector2f GetPlayerArrayCoos();
            int GetPlayerId();
            void SetPlayerOrientation(int);
            void SetPlayerBroadcast(std::string, std::shared_ptr<sf::Texture>, std::string);
            void DisplayPlayer(sf::RenderWindow&);
            void SetPlayerTeamTag(sf::Vector2f, std::shared_ptr<sf::Color>);
            void MovePlayer(sf::Vector2f);
            void ReplaceBroadcast();
            std::string setMessageResponsive(std::string);
            std::string GetPlayerTeamName();
            int GetPlayerLevel();

            std::unique_ptr<AElem> playerElem;

        private:
            sf::ConvexShape _playerTag;
            sf::Color _playerTagColor;

            sf::Text _broadcastText;
            sf::Font _broadcastFont;
            std::unique_ptr<AElem> _broadcast;
            sf::Clock _broadcastDisplayTime;
            sf::Vector2f _bdcstResize;

            std::string _playerTeamName;
            int _playerId;
            int _playerLevel;
            int _playerOrientation;
            std::unique_ptr<Animation> _anm;
            sf::Vector2f _arrayCoo;
            sf::Vector2f _gameResize;
    };
}

static const std::map<int, int> ROTATERIGHT = {
    {N, E},
    {E, S},
    {S, W},
    {W, N},
};

static const std::map<int, int> ROTATELEFT = {
    {E, N},
    {S, E},
    {W, S},
    {N, W},
};

#endif /* !PLAYER_HPP_ */
