#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

namespace knights
{
    namespace map
    {
        class Map : sf::NonCopyable
        {
            public:
                Map(std::string map_name);
                ~Map();

            private:
                void _init_map() const;

                /* Tile width */
                int _tile_w;

                /* Tile height */
                int _tile_h;

                /* Number of tiles in X axis */
                int _tiles_x;

                /* Number of tiles in Y axis */
                int _tiles_y;

                std::string _map_name;
        };
    }
}

#endif
