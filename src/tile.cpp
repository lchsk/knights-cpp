#include "tile.h"

namespace ks
{
    Tile::Tile(std::unique_ptr<sf::Sprite>&& sprite, int x, int y)
        : _x(x),
          _y(y),
          _tile(std::move(sprite))
    {
        _tile->setPosition(x, y);
    }

    Tile::~Tile()
    {

    }

    void Tile::render(sf::RenderWindow& window)
    {
        window.draw(*_tile);
    }
}
