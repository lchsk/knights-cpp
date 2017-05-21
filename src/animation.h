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
        Animation(const std::shared_ptr<ks::Spritesheet>& spritesheet,
                  const std::vector<int>& frames);
        Animation(const std::shared_ptr<ks::Spritesheet>& spritesheet,
                  const std::vector<sf::IntRect>& rects);
        ~Animation();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        bool is_playing();
        void play();
        void stop();
        void reset();

        void set_speed(const float speed);
        void set_position(const double x, const double y) const;

        const sf::Vector2i get_size() const;

    private:
        void _init();
        void _set_offset();

        std::vector<std::unique_ptr<sf::Sprite> > _frames;

        /* Current frame */
        int _frame;

        int _offset_w;
        int _offset_h;

        sf::Time _since_update;

        float _speed;
        bool _is_playing;
    };
}

#endif
