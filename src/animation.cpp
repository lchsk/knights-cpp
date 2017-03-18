#include "animation.h"
#include "util.h"

namespace ks
{
    Animation::Animation(
        const std::shared_ptr<ks::Spritesheet>& spritesheet,
        const std::vector<int>& frames
    ) :
        _speed(1.0f)
    {
        reset();

        auto& texture = spritesheet->get_texture();

        auto texture_size = texture->getSize();

        for (int frame : frames) {
            _frames.push_back(std::move(spritesheet->get_new_sprite(frame)));
        }
    }

    Animation::~Animation()
    {
    }

    void Animation::update(sf::Time delta)
    {
        if (! _is_playing) return;

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

    void Animation::render(sf::RenderWindow& window)
    {
        if (_is_playing)
            window.draw(*_frames[_frame]);
    }

    bool Animation::is_playing()
    {
        return _is_playing;
    }
    
    void Animation::play()
    {
        _is_playing = true;
    }

    void Animation::stop()
    {
        _is_playing = false;
    }

    void Animation::reset()
    {
        _is_playing = false;
        _frame = -1;

        // Large value to force an update
        _since_update = sf::seconds(99999);
    }

    void Animation::set_speed(const float speed)
    {
        _speed = speed;
    }

    void Animation::set_position(const double x, const double y) const
    {
        const auto pos = sf::Vector2f(
            x - ks::UNIT_OFFSET_W, y - ks::UNIT_OFFSET_H);

        for (auto& frame : _frames) {
            frame->setPosition(pos);
        }
    }
}
