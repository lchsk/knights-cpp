#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include "resource_mgr.h"
#include "animation.h"
#include "tile.h"
#include "character.h"

namespace ks
{
    class Map
    {
    public:
        Map(std::shared_ptr<ks::ResourceMgr> resource_mgr,
            std::string map_name);
        ~Map();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window,
                    std::vector<std::shared_ptr<ks::Character> >& characters);

    private:
        void _init_map() const;

        std::shared_ptr<ks::ResourceMgr>
            _resource_mgr;

        std::vector<
            std::unique_ptr<ks::Tile>
            > _tiles;

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

#endif
