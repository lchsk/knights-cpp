#include "animation.h"
#include "util.h"

namespace ks
{
    Animation::Animation(
        const std::shared_ptr<ks::Spritesheet>& spritesheet,
        const std::vector<int>& frames)
    {
        _init();

        for (int frame : frames) {
            _frames.push_back(std::move(spritesheet->get_new_sprite(frame)));
        }

        _set_offset();
        set_position(0, 0);
    }

    Animation::Animation(const std::shared_ptr<ks::Spritesheet>& spritesheet,
                         const std::vector<sf::IntRect>& rects)
    {
        _init();

        for (sf::IntRect rect : rects) {
            _frames.push_back(std::move(spritesheet->get_new_sprite(rect)));
        }

        _set_offset();
        set_position(0, 0);
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
        if (_frame < 0)
            _frame = 0;

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

    void Animation::set_position(const double x, const double y)
    {
        _x = x - _offset_w;
        _y = y - _offset_h;

        const auto pos = sf::Vector2f(std::round(_x),
                                      std::round(_y));

        for (auto& frame : _frames) {
            frame->setPosition(pos);
        }
    }

    const sf::Vector2f Animation::get_position() const
    {
        return sf::Vector2f(_x, _y);
    }

    const sf::Vector2i Animation::get_size() const
    {
        if (_frames.size()) {
            return sf::Vector2i(GET_SPRITEP_WIDTH(_frames[0]),
                                GET_SPRITEP_HEIGHT(_frames[0]));
        } else {
            return sf::Vector2i(0, 0);
        }
    }

    const sf::Vector2i Animation::get_size_tiles() const
    {
        const sf::Vector2i size = get_size();

        return sf::Vector2i(ceil(size.x / PX_PER_VF), ceil(size.y / PX_PER_VF));
    }

    void Animation::_init()
    {
        _speed = 1.0;
        _x = 0;
        _y = 0;
        reset();
    }

    void Animation::_set_offset()
    {
        if (_frames.size()) {
            _offset_w = GET_SPRITEP_WIDTH(_frames[0]) / 2;
            _offset_h = GET_SPRITEP_HEIGHT(_frames[0]) / 2;
        } else {
            _offset_w = _offset_h = 0;
        }
    }
}
