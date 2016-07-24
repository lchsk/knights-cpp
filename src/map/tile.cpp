#include "tile.h"

namespace knights
{
    namespace map
    {
        Tile::Tile(sf::Sprite& sprite, int x, int y)
            : _x(x),
              _y(y),
              _tile(sprite)
        {
            // _map = std::make_unique<knights::map::Map>(
            //     resource_mgr,
            //     "test"
            // );

            _tile.setPosition(x, y);
        }

        Tile::~Tile()
        {

        }

        sf::Sprite&
        Tile::get_sprite()
        {
            return _tile;
        }

        void
        Tile::render(sf::RenderWindow& window)
        {
            // _map->render(window);
        }
    }
}
