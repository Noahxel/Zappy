/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Graphical
*/

#include "Graphical.hpp"

namespace GUI {
    Graphical::Graphical(int ac, char **av) :
        _gameWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Zappy")),
        _server(ac, av, _gameWindow),
        _world(_gameWindow),
        _pi(_gameWindow),
        _isMousePressed(false),
        _haveToRmPlayerFromInterface(false)
    {
        _gameWindow->setFramerateLimit(60);
        InitGUI();
        RunGUI();
    }

    Graphical::~Graphical()
    {
    }

    void Graphical::InitGUI()
    {
        _server.WaitForServer("WELCOME\n");
        _server.WriteToServer("GRAPHIC\n");
        _server.WriteToServer("tna\n");
        _server.WriteToServer("msz\n");
        _server.WriteToServer("mct\n");
        _server.WriteToServer("sgt\n");
        _server.WriteToServer("pwa\n");
    }

    void Graphical::GetDataFromServer()
    {
        std::vector<std::string> readed;
        std::vector<std::string> singleCmd;

        if ((readed = _server.ReadFromServer()).size() > 0) {
            for (std::size_t i = 0; i < readed.size(); i++) {
                singleCmd = MyCppLib::splitString(readed[i], ' ');
                _world.CmdRedirect(singleCmd);
                if (singleCmd[0] == "msz") // condition pour verifier si les tna ont été effectués
                    _pi.setTeamsInfos(_world.getTeamsInfos());
                if (singleCmd[0] == "pdi")
                    _haveToRmPlayerFromInterface = true;
            }
        }
    }

    void Graphical::handleGameEvents()
    {
        if (_refreshInterfaceClock.getElapsedTime().asMilliseconds() > 100) {
            std::vector<int> playerLevels = _world.GetPlayerLevelsByTeamname(_pi.getDisplayedTeamName());

            if (playerLevels.size() > 0 || _haveToRmPlayerFromInterface) {
                _pi.setPlayerLevel(_world.GetPlayerLevelsByTeamname(_pi.getDisplayedTeamName()));
                _haveToRmPlayerFromInterface = false;
            }
            _refreshInterfaceClock.restart();
        }

        while (_gameWindow->pollEvent(_gameEvents)) {
            if (_gameEvents.type == sf::Event::Closed) {
                _gameWindow->close();
            }
            if (_gameEvents.type == sf::Event::MouseWheelMoved) {
                if (_gameEvents.mouseWheel.delta > 0) {
                    _world.viewZoomIn();
                } else if (_gameEvents.mouseWheel.delta < 0) {
                    _world.viewZoomOut();
                }
            }
            if (_gameEvents.type == sf::Event::KeyPressed) {
                if (_gameEvents.key.code == sf::Keyboard::Add) {
                    _world.viewZoomIn();
                } else if (_gameEvents.key.code == sf::Keyboard::Subtract) {
                    _world.viewZoomOut();
                }
            }
            else if (_gameEvents.type == sf::Event::MouseButtonPressed) {
                if (_gameEvents.mouseButton.button == sf::Mouse::Left) {
                    _mouseLastPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_gameWindow));
                    _isMousePressed = true;
                    if (_pi.changeTeamSpec(_mouseLastPos))
                        continue;
                    _world.checkClickOnPlayer();
                        
                }
            }
            else if (_gameEvents.type == sf::Event::MouseButtonReleased) {
                if (_gameEvents.mouseButton.button == sf::Mouse::Left) {
                    _isMousePressed = false;
                }
            }
            else if (_gameEvents.type == sf::Event::MouseMoved) {
                if (_isMousePressed) {
                    sf::Vector2f currentMousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_gameWindow));
                    sf::Vector2f offset = _mouseLastPos - currentMousePos;
                    if (_mouseClock.getElapsedTime().asMilliseconds() > 10) {
                        _mouseLastPos = currentMousePos;
                        _mouseClock.restart();
                    }
                    _world.moveView(offset);
                }
            }
        }
    }

    void Graphical::RunGUI()
    {
        std::string winners;
        sf::Font font;
        sf::Texture bgTexture;

        while (_gameWindow->isOpen() && (winners = _world.isGameEnded()).empty()) {
            handleGameEvents();
            GetDataFromServer();
            _gameWindow->clear(sf::Color::Black);
            _world.DisplayWorld();
            _pi.displayPlayerInterface();
            _gameWindow->display();
        }

        if (!font.loadFromFile(FONT_PATH))
            throw std::runtime_error("cant load font\n");
        if (!bgTexture.loadFromFile(GOODBY_BG_PATH))
            throw std::runtime_error("cant load bgTexture\n");

        winnersText.setString("team " + winners + " won the game");
        winnersText.setFont(font);
        winnersText.setPosition(sf::Vector2f(600, 450));
        winnersText.setCharacterSize(60);

        _goodbyBG = std::make_unique<AElem>("goodbyBg", std::make_shared<sf::Texture>(bgTexture));

        while (_gameWindow->isOpen()) {
            while (_gameWindow->pollEvent(_gameEvents)) {
                if (_gameEvents.type == sf::Event::Closed) {
                    _gameWindow->close();
                    return;
                }
                if (_gameEvents.type == sf::Event::KeyPressed) {
                    if (_gameEvents.key.code == sf::Keyboard::Escape) {
                        _gameWindow->close();
                        return;
                    }
                }
            }
            _gameWindow->clear();
            _gameWindow->draw(_goodbyBG->GetElemSprite());
            _gameWindow->draw(winnersText);
            _goodbyBG->SetElemPos(sf::Vector2f(0, 0));
            _gameWindow->display();
        }
    }
}
