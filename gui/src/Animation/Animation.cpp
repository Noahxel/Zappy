/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Animation
*/

#include "Animation.hpp"

namespace GUI {
    Animation::Animation(int start, int step, int maxRect, int animationSpeed) :
        _step(step),
        _maxRect(maxRect),
        _animationSpeedAsMs(animationSpeed),
        _start(start)
    {
        _elapsed = _animClock.restart();
        _spriteRect = {0, 0, step, step};
    }

    Animation::~Animation()
    {
    }

    sf::IntRect Animation::Animate()
    {
        _elapsed = _animClock.getElapsedTime();
        if (_elapsed.asMilliseconds() > _animationSpeedAsMs) {
            if (_spriteRect.left >= _maxRect)
                _spriteRect.left = _start;
            else
                _spriteRect.left += _step;
            _elapsed = _animClock.restart();
        }
        return (_spriteRect);
    }
}
