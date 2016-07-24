#include "animation.h"

namespace knights
{
    Animation::Animation(
        // std::shared_ptr<knights::Spritesheet>& spritesheet
        knights::Spritesheet& spritesheet
        ) :
        _spritesheet(spritesheet)
    {

    }

    Animation::~Animation()
    {

    }

    void
    Animation::update(sf::Time delta)
    {

    }

    void
    Animation::render(sf::RenderWindow& window)
    {
        auto s = _spritesheet.get(1, 0);
        s.setPosition(200, 300);
        window.draw(s);
    }
}
