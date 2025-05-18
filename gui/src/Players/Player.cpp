/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Player
*/

#include "Player.hpp"

namespace GUI {
    Player::Player(int clientId, std::vector<int> playerPos, int playerLevel, std::string teamName, std::shared_ptr<sf::Texture> playerTexture)
    {
        std::unique_ptr<AElem> player = std::make_unique<AElem>("player", playerTexture);

        _playerId = clientId;
        _playerLevel = playerLevel;
        _playerTeamName = teamName;
        playerElem = std::move(player);
        playerElem->SetElemPos({static_cast<float>(playerPos[0]), static_cast<float>(playerPos[1])});
        SetPlayerOrientation(playerPos[2]);

        if (!_broadcastFont.loadFromFile(FONT_PATH))
            throw std::runtime_error("Cannot load font for player");
        _broadcastText.setFont(_broadcastFont);
        _anm = nullptr;
        _broadcast = nullptr;
        PlayerSetLevel();
    }

    void Player::SetPlayerTeamTag(sf::Vector2f resize, std::shared_ptr<sf::Color> circleColor)
    {
        sf::Vector2f charPos = playerElem->GetElemCoo();
        sf::Vector2f charSize = playerElem->GetElemSize();

        _gameResize = resize;

        _playerTagColor = *circleColor;
        _playerTag.setPointCount(4);
        _playerTag.setPoint(0, sf::Vector2f(charPos.x + (charSize.x / 2), charPos.y));
        _playerTag.setPoint(1, sf::Vector2f(charPos.x + (charSize.x / 2) - (7 * resize.x), charPos.y + (7 * resize.x)));
        _playerTag.setPoint(2, sf::Vector2f(charPos.x + (charSize.x / 2), charPos.y + (22 * resize.x)));
        _playerTag.setPoint(3, sf::Vector2f(charPos.x + (charSize.x / 2) + (7 * resize.x), charPos.y + (7 * resize.x)));
        _playerTag.setFillColor(*circleColor);
        _playerTag.setOutlineColor(sf::Color::Black);
        _playerTag.setOutlineThickness(charSize.x / 40);
    }

    void Player::SetPlayerOrientation(int orientation)
    {
        _playerOrientation = orientation;

        if (_playerOrientation == N)
            playerElem->SetElemRect({1020, 0, 85, 85});
        if (_playerOrientation == S)
            playerElem->SetElemRect({680, 0, 85, 85});
        if (_playerOrientation == W)
            playerElem->SetElemRect({340, 0, 85, 85});
        if (_playerOrientation == E)
            playerElem->SetElemRect({85, 0, 85, 85});
    }

    void Player::ReplaceBroadcast()
    {
        sf::Vector2f broadcastPos = {playerElem->GetElemCoo().x - (9 * _gameResize.x), playerElem->GetElemCoo().y - (100 * _gameResize.x)};
        sf::Vector2f textPos = {playerElem->GetElemCoo().x + 2, playerElem->GetElemCoo().y - (100 * _gameResize.x)};

        _broadcast->SetElemPos(broadcastPos);
        _broadcastText.setPosition(textPos);
    }

    std::string Player::setMessageResponsive(std::string message)
    {
        std::string toreturn;

        for (std::size_t i = 0; i < message.size(); i++) {
            toreturn.push_back(message[i]);
            if (i % 7 == 0 && i != 0)
                toreturn.push_back('\n');
        }
        return (toreturn);
    }

    void Player::SetPlayerBroadcast(std::string bdcstName, std::shared_ptr<sf::Texture> bdcstTexture, std::string message)
    {
        std::unique_ptr<AElem> broadcast = std::make_unique<AElem>(bdcstName, bdcstTexture);

        _broadcast = std::move(broadcast);
        ReplaceBroadcast();
        _broadcast->ScaleElem(_gameResize);

        _broadcastText.setString(setMessageResponsive(message));
        _broadcastText.setScale(_gameResize);
        _broadcastText.setFillColor(sf::Color::Black);
        _broadcastText.setCharacterSize(19);
        _broadcastDisplayTime.restart();
    }

    int Player::GetPlayerId()
    {
        return (_playerId);
    }

    void Player::DisplayPlayer(sf::RenderWindow& window)
    {
        if (_broadcast) {
            if (_broadcastDisplayTime.getElapsedTime().asMilliseconds() > 5000)
                _broadcast.release();
            else {
                window.draw(_broadcast->GetElemSprite());
                window.draw(_broadcastText);
            }
        }
        window.draw(playerElem->GetElemSprite());
        window.draw(_playerTag);
    }

    void Player::MovePlayer(sf::Vector2f newCoos)
    {
        playerElem->SetElemPos(newCoos);
        if (_broadcast)
            ReplaceBroadcast();
        SetPlayerTeamTag(_gameResize, std::make_shared<sf::Color>(_playerTagColor));
    }

    void Player::PlayerSetLevel(bool isALevelUp)
    {
        if (isALevelUp)
            _playerLevel++;
        sf::Texture text;
        std::string pathToSprite = PLAYER_ASSETS_PATH + static_cast<std::string>("player") + std::to_string(_playerLevel) + ".png";

        if (!text.loadFromFile(pathToSprite))
            throw std::runtime_error("Cannot load texture player lvl " + std::to_string(_playerLevel));
        playerElem->SetElemTexture(std::make_shared<sf::Texture>(text));

    }

    sf::Sprite Player::GetPlayerSprite()
    {
        return (playerElem->GetElemSprite());
    }

    void Player::SetPlayerArrayCoos(sf::Vector2f coos)
    {
        _arrayCoo = coos;
    }

    sf::Vector2f Player::GetPlayerArrayCoos()
    {
        return (_arrayCoo);
    }

    std::string Player::GetPlayerTeamName()
    {
        return (_playerTeamName);
    }

    int Player::GetPlayerLevel()
    {
        return (_playerLevel);
    }

    Player::~Player()
    {
        playerElem.release();
    }
}
