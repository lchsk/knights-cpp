#include "tile.h"

namespace ks
{
    Tile::Tile(std::unique_ptr<sf::Sprite>&& sprite, const int x, const int y,
               const int spritesheet_id, const int tile_id)
        : _x(x),
          _y(y),
          _spritesheet_id(spritesheet_id),
          _tile_id(tile_id),
          _sprite(std::move(sprite))
    {
        _sprite->setPosition(x, y);
    }

    Tile::~Tile()
    {

    }

    void Tile::render(sf::RenderWindow& window)
    {
        window.draw(*_sprite);
    }
}
