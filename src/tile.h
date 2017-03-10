#ifndef TILE_H
#define TILE_H

#include <memory>

#include <SFML/Graphics.hpp>

namespace ks
{
    class Tile
    {
    public:
        Tile(std::unique_ptr<sf::Sprite>&& sprite, int x, int y);
        ~Tile();

        /* void update(sf::Time delta); */
        void render(sf::RenderWindow& window);

    private:
        std::unique_ptr<sf::Sprite> _tile;

        int _x;
        int _y;
    };
}

#endif
