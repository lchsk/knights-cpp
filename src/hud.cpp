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
        for (const auto& c : _containers) {
            c->update_events(pos);
        }
    }

    bool Hud::left_click(const sf::Vector2i& pos)
    {
        std::cout << "hello\n";
        std::cout << pos.x << " " << pos.y << std::endl;
    }

    void Hud::render(sf::RenderWindow& window)
    {
        for (const auto& c : _containers) {
            c->render(window);
        }
    }

    void Hud::add(std::unique_ptr<ks::Container>&& c)
    {
        _containers.push_back(std::move(c));
    }
}
