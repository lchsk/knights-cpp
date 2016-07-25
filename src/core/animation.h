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

        bool is_playing();
        void play();
        void stop();
        void reset();
        void set_speed(float speed);

    private:
        knights::Spritesheet& _spritesheet;

        /* IDs of frames from _spritesheet */
        std::vector<int> _frames;

        /* Current frame */
        int _frame;

        sf::Time _since_update;

        float _speed;

        bool _is_playing;
    };
}

#endif
