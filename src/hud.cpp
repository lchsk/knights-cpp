#include "hud.h"

#include <iostream>

namespace ks
{
    Hud::Hud()
    {
    }

    Hud::~Hud()
    {
    }

    void Hud::update(sf::Time delta)
    {
    }

    void Hud::update_events(const sf::Vector2i& pos)
    {
        for (const auto& w : _widgets) {
            w->update_events(pos);
        }
    }

    bool Hud::left_click(const sf::Vector2i&)
    {

    }

    void Hud::render(sf::RenderWindow& window)
    {
        for (const auto& w : _widgets) {
            w->render(window);
        }
    }

    void Hud::add_widget(std::unique_ptr<ks::Button>&& w)
    {
        _widgets.push_back(std::move(w));
    }
}
