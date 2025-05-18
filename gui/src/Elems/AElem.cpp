/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AElem
*/

#include "AElem.hpp"

namespace GUI {
    AElem::AElem(std::string elemName, std::shared_ptr<sf::Texture> texture) :
        _elemPos(0, 0),
        _elemScale(1, 1),
        _name(elemName)
    {
        _anm = nullptr;
        SetElemTexture(texture);
    }

    AElem::~AElem()
    {
    }

    void AElem::SetElemRect(sf::IntRect textRect)
    {
        _textureRect = std::make_unique<sf::IntRect>(textRect);
        _elemSprite.setTextureRect(textRect);
    }

    sf::Sprite AElem::GetElemSprite()
    {
        if (_anm)
            _elemSprite.setTextureRect(_anm->Animate());

        return (_elemSprite);
    }

    sf::Vector2f AElem::GetElemCoo()
    {
        return (_elemSprite.getPosition());
    }

    void AElem::SetElemPos(sf::Vector2f newPos)
    {
        _elemSprite.setPosition(newPos);
    }

    void AElem::SetItemOpacity(int a)
    {
        sf::Color spriteColor = _elemSprite.getColor();

        spriteColor.a = a;
        _elemSprite.setColor(spriteColor);
    }

    void AElem::SetElemTexture(std::shared_ptr<sf::Texture> texture)
    {
        sf::Texture movedTexture = std::move(*texture);

        _elemTexture = movedTexture;
        _elemSprite.setTexture(_elemTexture);
    }

    void AElem::AnimateElem(int start, int step, int maxRect, int animationSpeed)
    {
        _anm = std::make_unique<Animation>(start, step, maxRect, animationSpeed);
    }

    void AElem::ScaleElem(sf::Vector2f newScale)
    {
        _elemScale = newScale;
        _elemSprite.setScale(_elemScale);
    }

    sf::Vector2f AElem::GetElemSize()
    {
        sf::FloatRect gb = _elemSprite.getGlobalBounds();
        sf::Vector2f size;

        size.x = gb.width;
        size.y = gb.height;

        return (size);
    }

    bool AElem::isPointOnElemCoos(sf::Vector2f point)
    {
        sf::Vector2f elemCoo = GetElemCoo();
        sf::Vector2f elemSize = GetElemSize();

        if ((point.x >= elemCoo.x && point.x <= (elemCoo.x + elemSize.x)) &&
            (point.y >= elemCoo.y && point.y <= (elemCoo.y + elemSize.y))) {
            return true;
        }

        return false;
    }
}
