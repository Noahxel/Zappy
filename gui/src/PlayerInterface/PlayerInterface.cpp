/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerInterface
*/

#include "PlayerInterface.hpp"

namespace GUI {
    PlayerInterface::PlayerInterface(std::shared_ptr<sf::RenderWindow> gameWindow) :
        _gameWindow(gameWindow)
    {
        sf::Texture playerTexture;
        std::string pathToTexture;
        sf::Texture leftTexture;
        sf::Texture rightTexture;
        sf::Texture levelArrayTexture;
        std::string idAsStr;

        currentTeamId = 0;

        if (!_font.loadFromFile(FONT_PATH))
            throw std::runtime_error("Cannot load font for team interface");
        _interfaceBgColor.r = 0;
        _interfaceBgColor.g = 0;
        _interfaceBgColor.b = 0;
        _interfaceBgColor.a = TRANSPARENT + 50;
        _interfaceBgSize = sf::Vector2f(300.f, 700.f);
        _interfaceBgPos = sf::Vector2f((1920 - _interfaceBgSize.x - 20), 20.f);
        _interfaceBg.setFillColor(_interfaceBgColor);
        _interfaceBg.setSize(_interfaceBgSize);
        _interfaceBg.setPosition(_interfaceBgPos);

        if (!leftTexture.loadFromFile(LEFT_TEXTURE_PATH))
            throw std::runtime_error("cant load left button texture\n");

        if (!rightTexture.loadFromFile(RIGHT_TEXTURE_PATH))
            throw std::runtime_error("cant load right button texture\n");

        _leftRightButtons.push_back(std::make_unique<AElem>("left", std::make_shared<sf::Texture>(leftTexture)));
        _leftRightButtons.back()->SetElemPos(sf::Vector2f(_interfaceBgPos.x + 10 , _interfaceBgPos.y + 30));
        _leftRightButtons.push_back(std::make_unique<AElem>("right", std::make_shared<sf::Texture>(rightTexture)));
        _leftRightButtons.back()->SetElemPos(sf::Vector2f(_interfaceBgPos.x + 240 , _interfaceBgPos.y + 30));

        if (!levelArrayTexture.loadFromFile(LEVEL_ARRAY_PATH))
            throw std::runtime_error("cant level array texture\n");

        _playerLevelArray = std::make_unique<AElem>("playerLevelArray", std::make_shared<sf::Texture>(levelArrayTexture));
        _playerLevelArray->SetElemPos(sf::Vector2f(_interfaceBgPos.x + 15 , _interfaceBgPos.y + 100));

        for (int i = 1; i < 9; i++) {
            idAsStr = std::to_string(i);
            pathToTexture = PLAYER_ASSETS_PATH + static_cast<std::string>("player") + idAsStr + ".png";
            if (!playerTexture.loadFromFile(pathToTexture))
                throw std::runtime_error("cant level player texture\n");
            _playerTextures.insert(std::make_pair("player" + idAsStr, std::make_shared<sf::Texture>(playerTexture)));
        }
    }

    PlayerInterface::~PlayerInterface()
    {
    }

    void PlayerInterface::setPlayerLevel(std::vector<int> playerLevels)
    {
        if (playerLevels.size() == 0) {
            _playerHeads.clear();
            return;
        }
        
        std::sort(playerLevels.begin(), playerLevels.end(), std::greater<int>());
        int nbPlayers = playerLevels.size();
        int prevlvl = playerLevels[0];
        sf::Vector2f initialPos = sf::Vector2f(_playerLevelArray->GetElemCoo().x + 5, _playerLevelArray->GetElemCoo().y + ((8 - prevlvl) * 75));
        sf::Vector2f headPos = initialPos;
        sf::Vector2f playerScale = {0.5, 0.5};

        _playerHeads.clear();

        for (int i = 0; i < nbPlayers; i++) {
            _playerHeads.push_back(std::make_unique<AElem>("PlayerHead", _playerTextures.at("player" + std::to_string(playerLevels[i]))));
            _playerHeads[i]->ScaleElem(playerScale);
            _playerHeads[i]->SetElemRect(sf::IntRect(683, 0, 80, 50));
            if (playerLevels[i] == prevlvl && i != 0) {
                headPos.x += 43;
            } else {
                headPos.y += (((prevlvl - playerLevels[i]) * 71) + (playerLevels[i]));
                headPos.x = initialPos.x;
            }
            _playerHeads[i]->SetElemPos(headPos);
            prevlvl = playerLevels[i];
        }
    }

    void PlayerInterface::setTeamsInfos(std::map<std::string, std::shared_ptr<sf::Color>> teamsInfos)
    {
        sf::Vector2f basicColorSquareSize = {150, 50};
        sf::Vector2f originalColorSquarePos = {_interfaceBgPos.x + 75, _interfaceBgPos.y + 30};
        sf::Vector2f textPos = sf::Vector2f(originalColorSquarePos.x + 10, originalColorSquarePos.y + 10);

        for (auto pair : teamsInfos) {
            team_t team;
            team._teamColorRect.setFillColor(*pair.second);
            team._teamColorRect.setPosition(originalColorSquarePos);
            team._teamColorRect.setSize(basicColorSquareSize);
            team._teamName.setString(pair.first);
            team._teamName.setPosition(textPos);
            team._teamName.setCharacterSize(20);
            team._teamName.setFillColor(sf::Color::Black);
            team._teamName.setFont(_font);
            teams.push_back(team);
        }
    }

    bool PlayerInterface::changeTeamSpec(sf::Vector2f mouseClick)
    {
        bool toreturn = false;

        if (_leftRightButtons[LEFT]->isPointOnElemCoos(mouseClick)) {
            _playerHeads.clear();
            toreturn = true;
            if (static_cast<std::size_t>(currentTeamId) == 0)
                currentTeamId = teams.size() - 1;
            else
                currentTeamId--;
        }

        if (_leftRightButtons[RIGHT]->isPointOnElemCoos(mouseClick)) {
            _playerHeads.clear();
            toreturn = true;
            if (static_cast<std::size_t>(currentTeamId) == teams.size() - 1)
                currentTeamId = 0;
            else
                currentTeamId++;
        }
        return (toreturn);
    }

    void PlayerInterface::displayPlayerInterface()
    {
        int nbHeads = _playerHeads.size();

        _gameWindow->setView(_gameWindow->getDefaultView());
        _gameWindow->draw(_interfaceBg);
        _gameWindow->draw(_playerLevelArray->GetElemSprite());
        if (teams.size() > 0) {
            _gameWindow->draw(teams[currentTeamId]._teamColorRect);
            _gameWindow->draw(teams[currentTeamId]._teamName);
            _gameWindow->draw(_leftRightButtons[LEFT]->GetElemSprite());
            _gameWindow->draw(_leftRightButtons[RIGHT]->GetElemSprite());
        }
        for (int i = 0; i < nbHeads; i++) {
            _gameWindow->draw(_playerHeads[i]->GetElemSprite());
        }
    }

    std::string PlayerInterface::getDisplayedTeamName()
    {
        return (teams[currentTeamId]._teamName.getString());
    }
}
