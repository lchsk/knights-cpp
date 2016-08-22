#ifndef TILE_H
#define TILE_H

#include <memory>

#include <SFML/Graphics.hpp>

/* #include "map.h" */
/* #include "../core/resource_mgr.h" */

namespace knights
{
    class Tile
    {
    public:
        Tile(sf::Sprite& sprite, int x, int y);
        ~Tile();

        /* void update(sf::Time delta); */
        void render(sf::RenderWindow& window);

        sf::Sprite&
            get_sprite();

    private:
        /* std::unique_ptr<sf::Sprite> _tile; */
        sf::Sprite _tile;
        int _x;
        int _y;
    };
}

#endif
