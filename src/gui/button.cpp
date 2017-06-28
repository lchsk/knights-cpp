#include <iostream>

#include "button.h"

namespace ks
{
    Button::Button() :
        _state(ButtonState::Ready)
    {
    }

    Button::~Button()
    {
    }

    const ButtonState Button::getState() const
    {
        return _state;
    }

    void Button::add_state(ButtonState state, std::unique_ptr<sf::Sprite>&& spr)
    {
        _state_sprites[state] = std::move(spr);
        // _state_sprites[state]->setPosition(sf::Vector2f(10, 10));
    }

    void Button::render(sf::RenderWindow& window)
    {
        if (_state_sprites.find(_state) != _state_sprites.end()) {
            window.draw(*_state_sprites[_state]);
        }
    }

    void Button::update_events(const sf::Vector2i& pos)
    {
        sf::Rect<int> r(0, 0, 32, 32);

        if (r.contains(pos)) {
            _state = ButtonState::Hover;
        } else {
            _state = ButtonState::Ready;
        }
    }
}
