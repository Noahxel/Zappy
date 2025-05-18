/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI {
    class Animation {
        public:
            Animation(int, int, int, int);
            ~Animation();
            sf::IntRect Animate();

        protected:
        private:
            sf::Time _elapsed;
            sf::Clock _animClock;
            sf::IntRect _spriteRect;
            int _step;
            int _maxRect;
            int _animationSpeedAsMs;
            int _start;
    };
}

#endif /* !ANIMATION_HPP_ */
