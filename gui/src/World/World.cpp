/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** World
*/

#include "World.hpp"

namespace GUI {
    World::World(std::shared_ptr<sf::RenderWindow> gameWindow)
    {
        _gameEnded = "";
        _window = gameWindow;
        if (!_lvlUpSoundBuffer.loadFromFile(INCANTATION_SOUND_PATH))
            throw std::runtime_error("Cannot load sound effect");        
        _lvlUpSound.setBuffer(_lvlUpSoundBuffer);
        _lvlUpSound.setVolume(50);

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        LoadWorldTextures();
        _elapsedTimeUnit = _timeUnitClock.restart();
        _refreshItemsElapsed = _refreshItemsClock.restart();

        _gameView = static_cast<sf::View>(sf::FloatRect(0, 0, 1920, 1080));
        _playerFocused = nullptr;
        _originalViewSize = _gameView.getSize();
        _originalViewCenter = _gameView.getCenter();
    }

    World::~World()
    {
    }

    void World::LoadWorldTextures()
    {
        std::ifstream file("gui/src/Elems/ElemsInfos");
        std::string line;

        if (!file.is_open())
            throw std::runtime_error("can't open ElemsInfos");
        while (getline(file, line)) {
            std::vector<std::string> elemDetail = MyCppLib::splitString(line, '|');
            sf::Texture text;
            if (!text.loadFromFile(ASSEETS_PATH + elemDetail[TEXTURE_PATH]))
                throw std::runtime_error("Cannot load texture " + elemDetail[TEXTURE_PATH ]);
            _textures.insert(std::make_pair(elemDetail[TEXTURE_NAME], std::make_shared<sf::Texture>(text)));
        }
    }

    void World::ReplaceItemsByGroundId(int groundId)
    {
        if (_worldMap[groundId].floorElems.size() > 0) {
            sf::Vector2f groundPos = _worldMap[groundId].ground->GetElemCoo();
            float tileWidth = _worldMap[groundId].ground->GetElemSize().x;
            float tileHeight = _worldMap[groundId].ground->GetElemSize().y;

            int numItems = _worldMap[groundId].floorElems.size();
            int numRows = std::ceil(std::sqrt(numItems));
            int numColumns = std::ceil(static_cast<float>(numItems) / numRows);

            float itemWidth = tileWidth / numColumns;
            float itemHeight = tileHeight / numRows;

            float scaleFactor = std::min(itemWidth / ITEM_SIZE, itemHeight / ITEM_SIZE);
            scaleFactor = std::min(scaleFactor, 1.0f);
            if (scaleFactor > _generalScale.x * BASIC_ITEM_SCALE)
                scaleFactor = _generalScale.x * BASIC_ITEM_SCALE;

            for (std::size_t j = 0; j < _worldMap[groundId].floorElems.size(); j++) {
                int row = j / numColumns;
                int column = j % numColumns;

                sf::Vector2f itemPos;
                itemPos.x = groundPos.x + (column * itemWidth) + (itemWidth - (ITEM_SIZE * scaleFactor)) / 2.0f;
                itemPos.y = groundPos.y + (row * itemHeight) + (itemHeight - (ITEM_SIZE * scaleFactor)) / 2.0f;

                _worldMap[groundId].floorElems[j]->SetElemPos(itemPos);
                _worldMap[groundId].floorElems[j]->ScaleElem({scaleFactor, scaleFactor});
            }
        }
    }

    std::vector<int> World::GetPlayersId()
    {
        std::vector<int> playersId;

        for (std::size_t i = 0; i < _players.size(); i++) {
            playersId.push_back(_players[i]->GetPlayerId());
        }

        return (playersId);
    }

    void World::RefreshItemsOpacity()
    {
        _refreshItemsElapsed = _refreshItemsClock.getElapsedTime();
        if (_refreshItemsElapsed.asSeconds() >= 1) {
            for (std::size_t i = 0; i < _worldMap.size(); i++) {
                if (isAPlayerHere(_worldMap[i].coos) > -1 || _worldMap[i].eggs.size() > 0)
                    ManageItemsOpacity(i, TRANSPARENT);
                else
                    ManageItemsOpacity(i, OPAQUE);
            }
            _refreshItemsClock.restart();
        }
    }

    void World::moveView(sf::Vector2f offset)
    {
        sf::Vector2f viewCenter = _gameView.getCenter();
        sf::Vector2f viewSize = _gameView.getSize();

        float xMin = viewSize.x / 2.0f;
        float xMax = 1920 - viewSize.x / 2.0f;
        float yMin = viewSize.y / 2.0f;
        float yMax = 1080 - viewSize.y / 2.0f;

        sf::Vector2f newCenter = viewCenter + offset;

        float clampedX = std::max(xMin, std::min(newCenter.x, xMax));
        float clampedY = std::max(yMin, std::min(newCenter.y, yMax));
        newCenter.x = clampedX;
        newCenter.y = clampedY;

        _playerFocused = nullptr;
        _gameView.setCenter(newCenter);
    }

    void World::viewZoomIn()
    {
        sf::Vector2f viewSize = _gameView.getSize();
        sf::Vector2f newViewSize = viewSize * (1.0f / (1.0f + ZOOM_FACTOR));

        if (newViewSize.x >= (1920 * (_generalScale.x * 1.35)) && newViewSize.y >= (1080 * (_generalScale.y * 1.35))) {
            _gameView.setSize(newViewSize);
        }
    }

    void World::viewZoomOut()
    {
        sf::Vector2f viewSize = _gameView.getSize();
        sf::Vector2f newViewSize = viewSize * (1.0f + ZOOM_FACTOR);

        if (newViewSize.x <= _originalViewSize.x && newViewSize.y <= _originalViewSize.y) {
            _gameView.setSize(newViewSize);
        } else
            _gameView.setSize(_originalViewSize);
        _playerFocused = nullptr;
    }

    void World::recenterView()
    {
        if (_playerFocused) {
            _gameView.setCenter(_playerFocused->playerElem->GetElemCoo() + sf::Vector2f(_playerFocused->playerElem->GetElemSize().x / 2, _playerFocused->playerElem->GetElemSize().y / 2));
        }
        _window->setView(_gameView);
    }

    void World::DisplayWorld()
    {
        RefreshItemsOpacity();
        _window->setView(_gameView);
        for (std::size_t i = 0; i < _basicGround.size(); i++)
            _window->draw(_basicGround[i]->GetElemSprite());
        for (std::size_t i = 0; i < _worldMap.size(); i++) {
            _window->draw(_worldMap[i].ground->GetElemSprite());
            if (_worldMap[i].floorElems.size() > 0)
                for (std::size_t j = 0; j < _worldMap[i].floorElems.size(); j++)
                    _window->draw(_worldMap[i].floorElems[j]->GetElemSprite());
            for (std::size_t k = 0; k < _worldMap[i].eggs.size(); k++)
                _window->draw(_worldMap[i].eggs[k].egg->GetElemSprite());
        }
        for (std::size_t i = 0; i < _players.size(); i++) {
            _players[i]->DisplayPlayer(*_window);
        }
        recenterView();
    }

    int World::GetRandBeetween(int min, int max)
    {
        int randomNumber = min + (std::rand() % (max - min + 1));

        return (randomNumber);
    }

    void World::InitWorld()
    {
        int BiggestOutMap = -1;
        int BiggestOutMapXY = -1;
        float resize = 1;

        _generalScale = {1, 1};
        if (_mapSize[X] - MAX_X_WO_SCALE > 0) {
            BiggestOutMapXY = X;
            BiggestOutMap = _mapSize[X] - MAX_X_WO_SCALE;
        }
        if ((BiggestOutMap < (_mapSize[Y] - MAX_Y_WO_SCALE) && (_mapSize[Y] - MAX_Y_WO_SCALE) > 0)) {
            BiggestOutMapXY = Y;
            BiggestOutMap = _mapSize[Y] - MAX_Y_WO_SCALE;
        }

        if (BiggestOutMap > 0) {
            resize = BiggestOutMapXY == X ? std::round(1800 / (100.0f * _mapSize[X]) * 100) / 100 : std::round(900 / (100.0f * _mapSize[Y]) * 100) / 100;
            _generalScale = {resize, resize};
        }

        _originalGroundPos.x = 910 - ((_mapSize[X] - 1) * (50 * resize)) + (resize > 0 && resize < 1 ? 25 : 0);
        _originalGroundPos.y = 465 - ((_mapSize[Y] - 1) * (50 * resize)) + (resize > 0 && resize < 1 ? 25 : 0);

        std::unique_ptr<AElem> elem;
        sf::Vector2f elemPos = {0, 0};
        std::string name;

        while (elemPos.y < 1080) {
            while (elemPos.x < 1920) {
                name = "water";
                elem = std::make_unique<AElem>(name, _textures.at(name));

                elem->ScaleElem(_generalScale);
                elem->SetElemPos(elemPos);
                if (GetRandBeetween(1, 20) == 1)
                    elem->AnimateElem(100, 100, 200, 500);
                _basicGround.push_back(std::move(elem));
                elemPos.x += GROUND_SIZE * resize;
            }
            elemPos.y += GROUND_SIZE * resize;
            elemPos.x = 0;
        }

        elemPos = {_originalGroundPos.x, _originalGroundPos.y};
        AElem* ground;
        sf::Vector2f coos;

        for (int i = 0; i < _mapSize[Y]; i++) {
            for (int j = 0; j < _mapSize[X]; j++) {
                if (j == 0) {
                    elem = std::make_unique<AElem>("groundTop", _textures.at("groundTop"));
                    elem->ScaleElem(_generalScale);
                    elem->SetElemPos({elemPos.x, elemPos.y - (GROUND_SIZE * _generalScale.y)});
                    _basicGround.push_back(std::move(elem));
                }
                if (j == _mapSize[X] - 1) {
                    elem = std::make_unique<AElem>("groundDown", _textures.at("groundDown"));
                    elem->ScaleElem(_generalScale);
                    elem->SetElemPos({elemPos.x, elemPos.y + (GROUND_SIZE * _generalScale.y)});
                    _basicGround.push_back(std::move(elem));
                }
                name = "ground" + std::to_string(GetRandBeetween(1, 2));
                ground = new AElem(name, _textures.at(name));

                ground->ScaleElem(_generalScale);
                ground->SetElemPos(elemPos);
                coos = {static_cast<float>(j), static_cast<float>(i)};
                _worldMap.push_back(ground_t(coos, ground));
                elemPos.x += GROUND_SIZE * resize;
            }
            elemPos.y += GROUND_SIZE * resize;
            elemPos.x = _originalGroundPos.x;
        }
        AddGroundCorners();
    }

    void World::AddGroundCorners()
    {
        std::unique_ptr<AElem> elem;
        int tileSize = GROUND_SIZE * _generalScale.x;

        for (std::size_t i = 0; i < _worldMap.size(); i++) {
            if (_worldMap[i].coos.x == 0 && _worldMap[i].coos.y == 0) {
                elem = std::make_unique<AElem>("groundTopLeft", _textures.at("groundTopLeft"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x - tileSize, _worldMap[i].ground->GetElemCoo().y - (tileSize - (45 * _generalScale.x))});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.x == _mapSize[X] - 1 && _worldMap[i].coos.y == 0) {
                elem = std::make_unique<AElem>("groundTopRight", _textures.at("groundTopRight"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x + tileSize, _worldMap[i].ground->GetElemCoo().y - (tileSize - (45 * _generalScale.x))});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.x == 0 && _worldMap[i].coos.y == _mapSize[Y] - 1) {
                elem = std::make_unique<AElem>("groundDownLeft", _textures.at("groundDownLeft"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x - tileSize, _worldMap[i].ground->GetElemCoo().y + tileSize});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.x == _mapSize[X] - 1 && _worldMap[i].coos.y == _mapSize[Y] - 1) {
                elem = std::make_unique<AElem>("groundDownRight", _textures.at("groundDownRight"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x + tileSize, _worldMap[i].ground->GetElemCoo().y + tileSize});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.x == 0) {
                elem = std::make_unique<AElem>("groundLeft", _textures.at("groundLeft"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x - tileSize, _worldMap[i].ground->GetElemCoo().y});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.y == 0) {
                elem = std::make_unique<AElem>("groundTop", _textures.at("groundTop"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x, _worldMap[i].ground->GetElemCoo().y - tileSize});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.x == _mapSize[X] - 1) {
                elem = std::make_unique<AElem>("groundRight", _textures.at("groundRight"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x + tileSize, _worldMap[i].ground->GetElemCoo().y});
                _basicGround.push_back(std::move(elem));
            }

            if (_worldMap[i].coos.y == _mapSize[Y] - 1) {
                elem = std::make_unique<AElem>("groundDown", _textures.at("groundDown"));
                elem->ScaleElem(_generalScale);
                elem->SetElemPos({_worldMap[i].ground->GetElemCoo().x, _worldMap[i].ground->GetElemCoo().y + tileSize});
                _basicGround.push_back(std::move(elem));
            }
        }
    }

    void World::CmdRedirect(std::vector<std::string> received)
    {
        const auto& it = REPSERV.find(received[0]);

        if (it != REPSERV.end()) {
            if (it->second != nullptr) {
                (this->*(it->second))(received);
            }
        }
    }

    std::string World::isGameEnded()
    {
        return (_gameEnded);
    }

    void World::interpretMsz(std::vector<std::string> received)
    {
        if (received.size() != 3)
            return;

        _mapSize.push_back(std::stoi(received[1]));
        _mapSize.push_back(std::stoi(received[2]));

        InitWorld();
        std::cout << "map size loaded: " << _mapSize[0] << " " << _mapSize[1] << std::endl;
    }

    bool World::IsTimeUnitElapsed()
    {
        _elapsedTimeUnit = _timeUnitClock.getElapsedTime();
        if (_elapsedTimeUnit.asSeconds() >= _timeUnit) {
            _timeUnitClock.restart();
            return (true);
        } else
            return (false);
    }

    void World::interpretBct(std::vector<std::string> received)
    {
        if (received.size() != 10)
            return;

        sf::Vector2f itemCoos = {std::stof(received[1]), std::stof(received[2])};
        int itemGroundId = 0;

        if ((itemGroundId = GetGroundIdByCoo(itemCoos)) < 0)
            return;

        int itemCount = 0;
        std::string itemName;

        _worldMap[itemGroundId].floorElems.clear();
        for (std::size_t j = 3; j < received.size(); j++) {
            itemName = ITEMCORES.at(j - 3);
            itemCount = std::stoi(received[j]);
            for (int i = 0; i < itemCount; i++) {
                _worldMap[itemGroundId].floorElems.push_back(std::make_unique<AElem>(itemName, _textures.at(itemName)));
            }
        }
        ReplaceItemsByGroundId(itemGroundId);
    }

    void World::interpretTna(std::vector<std::string> received)
    {
        if (received.size() != 2)
            return;

        std::string teamName = received[1];

        auto it = _TeamColors.find(teamName);
        if (it != _TeamColors.end()) {
            std::cout << "team already handeled\n";
            return;
        }

        int red = GetRandBeetween(100, 255);
        int green = GetRandBeetween(100, 255);
        int blue = GetRandBeetween(100, 255);

        sf::Color color = {static_cast<sf::Uint8>(red), static_cast<sf::Uint8>(green), static_cast<sf::Uint8>(blue), 255 };

        _TeamColors.insert(std::make_pair(received[1], std::make_shared<sf::Color>(color)));
    }

    int World::GetPlayerById(int id)
    {
        for (std::size_t j = 0; j < _players.size(); j++)
            if (id == _players[j]->GetPlayerId())
                return j;
        return -1;
    }

    int World::isAPlayerHere(sf::Vector2f coos)
    {
        for (std::size_t j = 0; j < _players.size(); j++)
            if (coos == _players[j]->GetPlayerArrayCoos())
                return j;
        return -1;
    }

    int World::GetGroundIdByCoo(sf::Vector2f coos)
    {
        for (std::size_t j = 0; j < _worldMap.size(); j++)
            if (coos == _worldMap[j].coos)
                return j;
        return -1;
    }

    void World::ManageItemsOpacity(int groundId, int opacity)
    {
        for (std::size_t j = 0; j < _worldMap[groundId].floorElems.size(); j++)
            _worldMap[groundId].floorElems[j]->SetItemOpacity(opacity);
    }

    void World::interpretPnw(std::vector<std::string> received)
    {
        if (received.size() != 7)
            return;

        int playerId = std::stoi(MyCppLib::removeCharFromStr(received[1], '#'));
        int inputedX = std::stoi(received[2]);
        int inputedY = std::stoi(received[3]);
        std::string teamName = received[6];
        sf::Vector2f arrayCoo = {static_cast<float>(inputedX), static_cast<float>(inputedY)};
        std::vector<int> playerPos;

        sf::Vector2f playerWorldCoos = GetElemWorldCooByGroundCoo(arrayCoo, PLAYER_SIZE);

        playerPos.push_back(playerWorldCoos.x);
        playerPos.push_back(playerWorldCoos.y);
        playerPos.push_back(std::stoi(received[4]));

        std::unique_ptr<Player> newPlayer = std::make_unique<Player>(playerId, playerPos, std::stoi(received[5]), teamName, _textures.at("egg"));

        newPlayer->playerElem->ScaleElem(_generalScale);
        newPlayer->playerElem->SetElemPos(playerWorldCoos);
        newPlayer->SetPlayerArrayCoos(arrayCoo);
        newPlayer->SetPlayerTeamTag(_generalScale, _TeamColors.at(teamName));
        _players.push_back(std::move(newPlayer));
    }

    sf::Vector2f World::GetElemWorldCooByGroundCoo(sf::Vector2f arrayCoo, int elemSpriteSize)
    {
        int groundId = GetGroundIdByCoo(arrayCoo);
        sf::Vector2f playerpos;

        sf::Vector2f groundCoos = _worldMap[groundId].ground->GetElemCoo();
        float playerCenteredX = groundCoos.x + (((_worldMap[groundId].ground->GetElemSize().x) - (elemSpriteSize * _generalScale.x)) / 2);
        float playerCenteredY = groundCoos.y + (((_worldMap[groundId].ground->GetElemSize().y) - (elemSpriteSize * _generalScale.y)) / 2);
        playerpos = {playerCenteredX, playerCenteredY};

        return (playerpos);
    }

    void World::interpretPpo(std::vector<std::string> received)
    {
        if (received.size() != 5)
            return;

        int id = std::stoi(received[1]);
        sf::Vector2f arrayCoos = {std::stof(received[2]), std::stof(received[3])};
        int orientation = std::stoi(received[4]);
        int playerId = 0;

        if ((playerId = GetPlayerById(id)) == -1) {
            std::cout << "cant find player\n";
            return;
        }

        _players[playerId]->SetPlayerOrientation(orientation);

        if (_players[playerId]->GetPlayerArrayCoos() == arrayCoos) {
            return;
        }

        _players[playerId]->SetPlayerArrayCoos(arrayCoos);
        // maybe short animation
        _players[playerId]->MovePlayer(GetElemWorldCooByGroundCoo(arrayCoos, PLAYER_SIZE));
        //
        _players[playerId]->SetPlayerOrientation(orientation);
    }

    void World::interpretPlv(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretPin(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretPex(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretPbc(std::vector<std::string> received)
    {
        if (received.size() < 3)
            return;
        
        int playerId = std::stoi(received[1]);
        std::string message;

        if ((playerId = GetPlayerById(playerId)) == -1) {
            std::cout << "unknown player for broadcast\n";
            return;
        }

        for (std::size_t i = 2; i < received.size(); i++) {
            message += received[i];
            if (i != received.size() - 1)
                message += " ";
        }
            

        _players[playerId]->SetPlayerBroadcast("talkbox", _textures.at("talkbox"), message);
    }

    int World::getIncatationByArrayCoos(sf::Vector2f incCoos)
    {
        for (std::size_t i = 0; i < _currentIncantations.size(); i++) {
            if (_currentIncantations[i].coos == incCoos)
                return (i);
        }
        return (-1);
    }

    void World::interpretPic(std::vector<std::string> received)
    {
        if (received.size() < 5)
            return;

        std::vector<std::shared_ptr<Player>> incantingPlayers;
        sf::Vector2f incantationPos = {std::stof(received[1]), std::stof(received[2])};
        int incantationLvl = std::stoi(received[3]);
        int playerId = -1;


        for (std::size_t i = 4; i < received.size(); i++) {
            if ((playerId = GetPlayerById(std::stoi(received[i]))) == -1) {
                return;
            }
            incantingPlayers.push_back(_players[playerId]);
        }
        incantation_t incantation(incantationPos, incantationLvl, incantingPlayers);
        _currentIncantations.push_back(incantation);
    }

    void World::interpretPie(std::vector<std::string> received)
    {
        if (received.size() != 4)
            return;

        sf::Vector2f incantationPos = {std::stof(received[1]), std::stof(received[2])};
        int result = std::stoi(received[3]);

        int incantationIndex = -1;
        for (std::size_t i = 0; i < _currentIncantations.size(); ++i) {
            if (_currentIncantations[i].coos == incantationPos) {
                incantationIndex = i;
                break;
            }
        }

        if (incantationIndex == -1) {
            std::cout << "Incantation not found: (" << incantationPos.x << ", " << incantationPos.y << ")" << std::endl;
            return;
        }

        if (result == 1) {
            _currentIncantations.erase(_currentIncantations.begin() + incantationIndex);
            std::cout << "Incantation failed :/\n";
            return;
        }

        for (std::size_t i = 0; i < _currentIncantations[incantationIndex].incantingPlayers.size(); ++i) {
            _currentIncantations[incantationIndex].incantingPlayers[i]->PlayerSetLevel(true);
        }

        _currentIncantations.erase(_currentIncantations.begin() + incantationIndex);
        _lvlUpSound.play();
        std::cout << "Incantation succeeded, players are going to level " << _currentIncantations[incantationIndex].incantationLevel + 1 << std::endl;
    }

    void World::interpretPfk(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretPdr(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretPgt(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretPdi(std::vector<std::string> received)
    {
        if (received.size() != 2)
            return;

        int playerId = std::stoi(MyCppLib::removeCharFromStr(received[1], '\n'));
        auto playerIndex = _players.begin();
        for (; playerIndex != _players.end(); ++playerIndex) {
            if ((*playerIndex)->GetPlayerId() == playerId) {
                break;
            }
        }

        _players.erase(playerIndex);
    }

    void World::interpretEnw(std::vector<std::string> received)
    {
        if (received.size() != 5)
            return;

        int id = std::stoi(received[1]);
        sf::Vector2f eggCoos = {std::stof(received[3]), std::stof(received[4])};
        sf::Vector2f eggCoosOnMap = GetElemWorldCooByGroundCoo(eggCoos, EGG_SIZE);
        int groundEggId = GetGroundIdByCoo(eggCoos);
        AElem* egg = new AElem("egg", _textures.at("egg"));

        egg->SetElemPos(eggCoosOnMap);
        egg->ScaleElem(_generalScale);
        _worldMap[groundEggId].eggs.push_back(egg_t(eggCoosOnMap, egg, id));
        std::cout << "eggpos on map: x = " << eggCoos.x << ", y = " << eggCoos.y << ", groundId = " << groundEggId << std::endl;
    }

    void World::interpretEbo(std::vector<std::string> received)
    {
        (void) received;
    }

    int World::getGroundByEggId(int id)
    {
        for (std::size_t i = 0; i < _worldMap.size() ; i++) {
            for (std::size_t j = 0; j < _worldMap[i].eggs.size(); j++) {
                if (_worldMap[i].eggs[j].eggId == id)
                    return (i);
            }
        }
        return (-1);
    }

    void World::interpretEdi(std::vector<std::string> received)
    {
        if (received.size() != 2)
            return;

        int eggId = std::stoi(received[1]);
        int eggGroundId = getGroundByEggId(eggId);

        if (eggGroundId == -1) {
            std::cout << "Egg not found with ID: " << eggId << std::endl;
            return;
        }

        auto& eggsList = _worldMap[eggGroundId].eggs;
        auto eggIt = std::find_if(eggsList.begin(), eggsList.end(), [eggId](const egg_t& egg) {
            return egg.eggId == eggId;
        });

        if (eggIt != eggsList.end()) {
            eggsList.erase(eggIt);
            std::cout << "Egg erased with ID: " << eggId << std::endl;
        }
    }

    void World::checkClickOnPlayer()
    {
        _window->setView(_window->getDefaultView());
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*_window);
        _window->setView(_gameView);

        sf::Vector2f worldPos = _window->mapPixelToCoords(pixelPos);

        for (std::size_t i = 0; i < _players.size(); i++) {
            if (_players[i]->playerElem->isPointOnElemCoos(worldPos)) {
                _playerFocused = _players[i];
                _gameView.setSize(_window->getDefaultView().getSize() / 3.5f);
                return;
            } 
        }
    }

    void World::interpretSgt(std::vector<std::string> received)
    {
        if (received.size() != 2)
            return;
        std::cout << "TIME UNIT: " << received[1] << std::endl;
        _timeUnit = std::stoi(received[1]);
    }

    void World::interpretSst(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretSeg(std::vector<std::string> received)
    {
        if (received.size() != 2)
            return;

        _gameEnded = received[1];
    }

    void World::interpretsmg(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretsuc(std::vector<std::string> received)
    {
        (void) received;
    }

    void World::interpretsbp(std::vector<std::string> received)
    {
        (void) received;
    }

    std::vector<int> World::GetPlayerLevelsByTeamname(std::string teamname)
    {
        std::vector<int> toReturn;

        for (std::size_t i = 0; i < _players.size(); i++) {
            if (_players[i]->GetPlayerTeamName() == teamname) {
                toReturn.push_back(_players[i]->GetPlayerLevel());
            }
        }
        return (toReturn);
    }

    std::map<std::string, std::shared_ptr<sf::Color>> World::getTeamsInfos()
    {
        return (_TeamColors);
    }
}
