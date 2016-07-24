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
            /* std::shared_ptr<knights::Spritesheet> spritesheet */
            knights::Spritesheet& spritesheet
        );
        ~Animation();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

    private:
        /* std::shared_ptr<knights::Spritesheet>& */
        knights::Spritesheet&
            _spritesheet;
    };
}

#endif
