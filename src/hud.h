#ifndef HUD_H
#define HUD_H

#include <memory>
#include <unordered_map>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>

namespace ks
{
    class Hud
    {
    public:
        Hud();
        ~Hud();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

    private:
    };
}

#endif
