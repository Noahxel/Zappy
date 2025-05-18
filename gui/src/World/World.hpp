/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** World
*/

#ifndef WORLD_HPP_
#define WORLD_HPP_
#include "AElem.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define X 0
#define Y 1
#define TEXTURE_NAME 0
#define TEXTURE_PATH 1
#define MAX_X_WO_SCALE 18
#define MAX_Y_WO_SCALE 9
#define ITEM_SIZE 33
#define GROUND_SIZE 100
#define PLAYER_SIZE 85
#define EGG_SIZE 60
#define TRANSPARENT 128
#define OPAQUE 255
#define ASSEETS_PATH "gui/assets/"
#define N 1
#define E 2
#define S 3
#define W 4
#define BASIC_ITEM_SCALE 1.5
#define FOCUS_ZOOM_FACTOR 700000
#define ZOOM_FACTOR 0.1f

namespace GUI {
    class World {
        public:
            World(std::shared_ptr<sf::RenderWindow> gameWindow);
            ~World();
            void LoadWorldTextures();
            void DisplayWorld();
            void InitWorld();
            void interpretMsz(std::vector<std::string>);
            void interpretBct(std::vector<std::string>);
            void interpretTna(std::vector<std::string>);
            void interpretPnw(std::vector<std::string>);
            void interpretPpo(std::vector<std::string>);
            void interpretPlv(std::vector<std::string>);
            void interpretPin(std::vector<std::string>);
            void interpretPex(std::vector<std::string>);
            void interpretPbc(std::vector<std::string>);
            void interpretPic(std::vector<std::string>);
            void interpretPie(std::vector<std::string>);
            void interpretPfk(std::vector<std::string>);
            void interpretPdr(std::vector<std::string>);
            void interpretPgt(std::vector<std::string>);
            void interpretPdi(std::vector<std::string>);
            void interpretEnw(std::vector<std::string>);
            void interpretEbo(std::vector<std::string>);
            void interpretEdi(std::vector<std::string>);
            void interpretSgt(std::vector<std::string>);
            void interpretSst(std::vector<std::string>);
            void interpretSeg(std::vector<std::string>);
            void interpretsmg(std::vector<std::string>);
            void interpretsuc(std::vector<std::string>);
            void interpretsbp(std::vector<std::string>);
            void CmdRedirect(std::vector<std::string>);
            int GetRandBeetween(int, int);
            void AddGroundCorners();
            bool IsTimeUnitElapsed();
            void ManageItemsOpacity(int, int);
            int isAPlayerHere(sf::Vector2f);
            int GetGroundIdByCoo(sf::Vector2f);
            int GetPlayerById(int);
            sf::Vector2f GetElemWorldCooByGroundCoo(sf::Vector2f, int);
            std::vector<int> GetPlayersId();
            int getGroundIdByPlayerId(int);
            void ReplaceItemsByGroundId(int);
            std::string isGameEnded();
            int getGroundByEggId(int);
            void RefreshItemsOpacity();
            int getIncatationByArrayCoos(sf::Vector2f);
            void recenterView();
            void viewZoomIn();
            void viewZoomOut();
            void moveView(sf::Vector2f offset);
            std::vector<int> GetPlayerLevelsByTeamname(std::string teamname);
            std::map<std::string, std::shared_ptr<sf::Color>> getTeamsInfos();
            void checkClickOnPlayer();

        private:
            typedef struct incantation_s {
                sf::Vector2f coos;
                int incantationLevel;
                std::vector<std::shared_ptr<Player>> incantingPlayers;

                incantation_s(sf::Vector2f coos, int incantationLevel, std::vector<std::shared_ptr<Player>> players)
                    : coos(coos), incantationLevel(incantationLevel), incantingPlayers(players)
                {}
            } incantation_t;

            typedef struct egg_s {
                sf::Vector2f coos;
                int eggId;
                AElem *egg;

                egg_s(sf::Vector2f _coos, AElem *_egg, int _id)
                    : coos(_coos), eggId(_id), egg(_egg)
                {
                    _egg->SetElemPos(coos);
                }
            } egg_t;

            typedef struct ground_s {
                sf::Vector2f coos;
                std::vector<std::unique_ptr<AElem>> floorElems;
                std::vector<egg_t> eggs;
                AElem *ground;

                ground_s(sf::Vector2f _coos, AElem *_ground)
                    : coos(_coos), ground(_ground)
                {}
            } ground_t;

            std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
            std::map<std::string, std::shared_ptr<sf::Color>> _TeamColors;
            std::shared_ptr<sf::RenderWindow> _window;
            std::vector<ground_t> _worldMap;
            std::vector<incantation_t> _currentIncantations;
            std::vector<std::unique_ptr<AElem>> _basicGround;
            std::vector<std::shared_ptr<Player>> _players;
            std::vector<int> _mapSize;
            sf::Vector2f _generalScale;
            sf::Vector2f _originalGroundPos;
            sf::Time _refreshItemsElapsed;
            sf::Clock _refreshItemsClock;
            int _timeUnit;
            sf::Time _elapsedTimeUnit;
            sf::Clock _timeUnitClock;
            std::string _gameEnded;

            float _zoomFactor;
            sf::View _gameView;
            std::shared_ptr<Player> _playerFocused;
            sf::Vector2f _originalViewSize;
            sf::Vector2f _originalViewCenter;
            sf::Sound _lvlUpSound;
            sf::SoundBuffer _lvlUpSoundBuffer;
    };
}

static const std::map<int, std::string> ITEMCORES = {
    {0, "food"},
    {1, "linemate"},
    {2, "deraumere"},
    {3, "sibur"},
    {4, "mendiane"},
    {5, "phiras"},
    {6, "thystame"}
};

static const std::map<std::string, void(GUI::World::*)(std::vector<std::string>)> REPSERV = {
    {"msz", &GUI::World::interpretMsz},
    {"bct", &GUI::World::interpretBct},
    {"tna", &GUI::World::interpretTna},
    {"pnw", &GUI::World::interpretPnw},
    {"ppo", &GUI::World::interpretPpo},
    {"plv", &GUI::World::interpretPlv},
    {"pin", &GUI::World::interpretPin},
    {"pex", &GUI::World::interpretPex},
    {"pbc", &GUI::World::interpretPbc},
    {"pic", &GUI::World::interpretPic},
    {"pie", &GUI::World::interpretPie},
    {"pfk", &GUI::World::interpretPfk},
    {"pdr", &GUI::World::interpretPdr},
    {"pgt", &GUI::World::interpretPgt},
    {"pdi", &GUI::World::interpretPdi},
    {"enw", &GUI::World::interpretEnw},
    {"ebo", &GUI::World::interpretEbo},
    {"edi", &GUI::World::interpretEdi},
    {"sgt", &GUI::World::interpretSgt},
    {"sst", &GUI::World::interpretSst},
    {"seg", &GUI::World::interpretSeg},
    {"smg", &GUI::World::interpretsmg},
    {"suc", &GUI::World::interpretsuc},
    {"sbp", &GUI::World::interpretsbp},
    {"WELCOME", nullptr}
};

#endif /* !WORLD_HPP_ */
