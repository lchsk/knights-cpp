#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "button.h"

namespace ks
{
    class Container {
    public:
        Container();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        void update_events(const sf::Vector2i& pos);

        void pack(std::unique_ptr<ks::Button>&& w);

    private:
      std::vector<std::unique_ptr<ks::Button> > _widgets;
    };
}
#endif
