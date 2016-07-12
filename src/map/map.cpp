#include "map.h"

namespace knights
{
    namespace map
    {
        Map::Map(
            std::shared_ptr<knights::res::ResourceMgr> resource_mgr,
            std::string map_name
        )
            : _map_name(map_name),
              _resource_mgr(resource_mgr)
        {
            _tile_w = 32;
            _tile_h = 32;

            _tiles_x = 70;
            _tiles_y = 50;

            _s.setTexture(_resource_mgr->get_texture("tiles"));
        }

        Map::~Map()
        {

        }

        void
        Map::update(sf::Time delta)
        {
        }

        void
        Map::render(sf::RenderWindow& window)
        {
            window.draw(_s);
        }

        void
        Map::_init_map() const
        {

        }
    }
}
