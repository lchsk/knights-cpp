#include "animation.h"

namespace knights
{
    Animation::Animation(
        knights::Spritesheet& spritesheet,
        std::vector<int>& frames
        ) :
        _spritesheet(spritesheet),
        _frames(frames),
        _frame(-1),
        _speed(.6f),
        // Large value needed to force an update
        _since_update(sf::seconds(99999))
    {

    }

    Animation::~Animation()
    {

    }

    void
    Animation::update(sf::Time delta)
    {
        if ((_since_update - delta).asSeconds()
            > (delta.asSeconds() / _speed)) {
            if (_frame >= _frames.size() - 1)
                _frame = 0;
            else
                _frame++;

            _since_update = sf::seconds(0);
        } else {
            _since_update += delta;
        }
    }

    void
    Animation::render(sf::RenderWindow& window)
    {
        // Enumerate spritesheet frames from 0
        int frame = _frames[_frame];

        auto tiles = _spritesheet.get_size();

        auto row = frame / tiles.x;
        auto col = frame % tiles.x;

        auto s = _spritesheet.get(row, col);
        s.setPosition(200, 300);
        window.draw(s);
    }
}
