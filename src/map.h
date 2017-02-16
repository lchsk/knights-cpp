#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include "resource_mgr.h"
#include "animation.h"
#include "tile.h"
#include "unit.h"
#include "data_loader.h"
#include "game_window.h"

namespace ks
{
    /* Side of each tile */
    const int TILE = 32;

    class Map
    {
    public:
        Map(std::shared_ptr<ks::ResourceMgr> resource_mgr,
            std::shared_ptr<ks::DataLoader> data_loader,
            std::shared_ptr<ks::GameWindow> window,
            std::string map_name);
        ~Map();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window,
                    std::vector<std::shared_ptr<ks::Unit> >& units);

    private:
        void _init_map() const;

        void load();

        std::shared_ptr<ks::ResourceMgr> _resource_mgr;
        std::shared_ptr<ks::GameWindow> _window;
        std::shared_ptr<ks::DataLoader> _data_loader;

        std::vector<
            std::unique_ptr<ks::Tile>
            > _tiles;

        /* Number of rows */
        int _tiles_rows;

        /* Number of columns */
        int _tiles_cols;

        std::string _map_name;
    };
}

#endif
