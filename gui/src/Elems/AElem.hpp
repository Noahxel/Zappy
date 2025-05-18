/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AElem
*/

#ifndef AELEM_HPP_
#define AELEM_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include "MyCppLib.hpp"
#include "Animation.hpp"
#define FONT_PATH "gui/assets/font.ttf"

namespace GUI
{
    class AElem {
        public:
            AElem(std::string, std::shared_ptr<sf::Texture>);
            ~AElem();
            void SetElemPos(sf::Vector2f);
            void SetElemTexture(std::shared_ptr<sf::Texture>);
            void AnimateElem(int, int, int, int);
            void ScaleElem(sf::Vector2f);
            sf::Sprite GetElemSprite();
            sf::Vector2f GetElemCoo();
            void SetElemRect(sf::IntRect);
            sf::Vector2f GetElemSize();
            void SetItemOpacity(int);
            bool isPointOnElemCoos(sf::Vector2f point);

        protected:
            sf::Vector2f _elemPos;
            sf::Texture _elemTexture;
            sf::Sprite _elemSprite;
            sf::Vector2f _elemScale;
            std::string _name;
            std::unique_ptr<Animation> _anm;
            std::unique_ptr<sf::IntRect> _textureRect;
    };
}

#endif /* !AELEM_HPP_ */
