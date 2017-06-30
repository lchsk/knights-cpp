#ifndef HUD_H
#define HUD_H

#include <memory>
#include <unordered_map>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "gui/button.h"

namespace ks
{
    class Hud
    {
    public:
        Hud();
        ~Hud();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        void update_events(const sf::Vector2i&);
        bool left_click(const sf::Vector2i&);

        void add_widget(std::unique_ptr<ks::Button>&&);

    private:
		std::vector<std::unique_ptr<ks::Button> > _widgets;
    };
}

#endif
