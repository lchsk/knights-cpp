#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include "../core/resource_mgr.h"
#include "../core/animation.h"
#include "tile.h"

namespace knights
{
    namespace map
    {
        class Map
        {
            public:
                Map(
                    std::shared_ptr<knights::res::ResourceMgr> resource_mgr,
                    std::string map_name
                );
                ~Map();

                void update(sf::Time delta);
                void render(sf::RenderWindow& window);

            private:
                void _init_map() const;

                std::shared_ptr<knights::res::ResourceMgr>
                    _resource_mgr;

                std::vector<
                    std::unique_ptr<knights::map::Tile>
                    > _tiles;

                std::shared_ptr<knights::Animation> _animation;

                /* Tile width */
                int _tile_w;

                /* Tile height */
                int _tile_h;

                /* Number of rows */
                int _tiles_rows;

                /* Number of columns */
                int _tiles_cols;

                std::string _map_name;
        };
    }
}

#endif
