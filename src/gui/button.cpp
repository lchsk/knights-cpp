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
        _size.read(*spr);

        _state_sprites[state] = std::move(spr);
    }

    void Button::render(sf::RenderWindow& window)
    {
        if (_state_sprites.find(_state) != _state_sprites.end()) {
            window.draw(*_state_sprites[_state]);
        }
    }

    void Button::update_events(const sf::Vector2i& pos)
    {
        sf::Rect<int> r(_state_sprites[_state]->getPosition().x,
                        _state_sprites[_state]->getPosition().y,
                        _size.width, _size.height);

        if (r.contains(pos)) {
            _state = ButtonState::Hover;
        } else {
            _state = ButtonState::Ready;
        }
    }

    void Button::set_position(const int x, const int y)
    {
        for (const auto& sprite : _state_sprites) {
            sprite.second->setPosition(sf::Vector2f(x, y));
        }
    }

    bool Button::left_click(const sf::Vector2i& pos)
    {
        sf::Rect<int> r(_state_sprites[_state]->getPosition().x,
                        _state_sprites[_state]->getPosition().y,
                        _size.width, _size.height);

        return r.contains(pos);
    }
}
