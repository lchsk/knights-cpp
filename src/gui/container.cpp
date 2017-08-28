#include <iostream>

#include "container.h"

namespace ks
{
    Container::Container()
    {
    }

    void Container::update(sf::Time delta)
    {
    }

    void Container::render(sf::RenderWindow& window)
    {
        for (const auto& w : _widgets) {
            w->render(window);
        }
    };

    void Container::update_events(const sf::Vector2i& pos)
    {
        for (const auto& w : _widgets) {
            w->update_events(pos);
        }
    };

    void Container::pack(std::unique_ptr<ks::Button>&& w)
    {
        _widgets.push_back(std::move(w));
    };
}
