#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "spritesheet.h"

namespace ks
{
    class Animation
    {
    public:
        Animation(
            const std::shared_ptr<ks::Spritesheet>& spritesheet,
            const std::vector<int>& frames
        );
        ~Animation();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        bool is_playing();
        void play();
        void stop();
        void reset();

        void set_speed(float speed);
        void set_position(double x, double y);

    private:
        std::vector<std::unique_ptr<sf::Sprite> > _frames;

        /* Current frame */
        int _frame;

        sf::Time _since_update;

        float _speed;
        bool _is_playing;
    };
}

#endif
