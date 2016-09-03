#include "animation.h"

namespace ks
{
    Animation::Animation(
        ks::Spritesheet& spritesheet,
        std::vector<int>& frames
    ) :
        _spritesheet(spritesheet),
        _frames(frames),
        _speed(1.0f)
    {
        reset();
    }

    Animation::~Animation()
    {

    }

    void
    Animation::update(sf::Time delta)
    {
        if (! _is_playing) return;

        if (
            (_since_update - delta).asSeconds()
            > (delta.asSeconds() / _speed)
        ) {
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

        auto s = _spritesheet.get(frame);

        window.draw(*s);
    }

    bool
    Animation::is_playing()
    {
        return _is_playing;
    }
    
    void
    Animation::play()
    {
        _is_playing = true;
    }

    void
    Animation::stop()
    {
        _is_playing = false;
    }

    void
    Animation::reset()
    {
        _is_playing = false;
        _frame = -1;

        // Large value to force an update
        _since_update = sf::seconds(99999);
    }

    void
    Animation::set_speed(float speed)
    {
        _speed = speed;
    }
}
