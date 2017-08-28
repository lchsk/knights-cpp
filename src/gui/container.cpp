#include <iostream>

#include "container.h"

namespace ks
{
    Container::Container() :
        _last_pos(0, 0)
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
        w->set_position(_last_pos.x, _last_pos.y);

        _last_pos.x += w->get_size().width;

        _widgets.push_back(std::move(w));
    };

    bool Container::left_click(const sf::Vector2i& pos)
    {
        for (const auto& w : _widgets) {
            if (w->left_click(pos))
                return true;
        }

        return false;
    }
}
