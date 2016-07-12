#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include "../core/resource_mgr.h"

namespace knights
{
    namespace map
    {
        class Map
        {
            public:
                Map(
                    std::shared_ptr<knights::res::ResourceMgr> resource_mgr,
                    std::string& map_name
                );
                ~Map();

                void update(sf::Time delta);
                void render(sf::RenderWindow& window);

            private:
                void _init_map() const;

                std::shared_ptr<knights::res::ResourceMgr> _resource_mgr;

                /* Tile width */
                int _tile_w;

                /* Tile height */
                int _tile_h;

                /* Number of tiles in X axis */
                int _tiles_x;

                /* Number of tiles in Y axis */
                int _tiles_y;

                std::string _map_name;

                sf::Sprite _s;
        };
    }
}

#endif
