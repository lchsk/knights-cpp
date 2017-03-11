#ifndef TILE_H
#define TILE_H

#include <memory>

#include <SFML/Graphics.hpp>

namespace ks
{
    class Tile
    {
    public:
        Tile(std::unique_ptr<sf::Sprite>&& sprite, const int x, const int y,
             const int spritesheet_id, const int tile_id);
        ~Tile();

        /* void update(sf::Time delta); */
        void render(sf::RenderWindow& window);

    private:
        std::unique_ptr<sf::Sprite> _sprite;

        const int _spritesheet_id;
        const int _tile_id;

        // In Pixels
        const int _x;
        const int _y;
    };
}

#endif
