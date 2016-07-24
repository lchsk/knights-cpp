#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "spritesheet.h"

namespace knights
{
    class Animation
    {
    public:
        Animation(
            knights::Spritesheet& spritesheet,
            std::vector<int>& frames
        );
        ~Animation();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

    private:
        knights::Spritesheet&
            _spritesheet;


        std::vector<int> _frames;
        int _frame;
        sf::Time _since_update;
        float _speed;
    };
}

#endif
