#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include "resource_mgr.h"
#include "animation.h"
#include "tile.h"
#include "unit.h"
#include "data_loader.h"
#include "game_window.h"
#include "graph.h"

namespace ks
{
    class Map
    {
    public:
        Map(std::shared_ptr<ks::ResourceMgr>& resource_mgr,
            std::shared_ptr<ks::DataLoader>& data_loader,
            std::shared_ptr<ks::GameWindow>& window,
            std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > >& units,
            std::string map_name);
        ~Map();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        void set_position(const std::shared_ptr<ks::Unit>& unit,
                          const int v) const;

        void move_unit(
            const std::shared_ptr<ks::Unit>& unit,
            const int x,
            const int y) const;

    private:
        void load();
        void _move_unit_step(
            const std::shared_ptr<ks::Unit>& unit, sf::Time& delta);

        std::unique_ptr<ks::Graph> _graph;

        std::shared_ptr<ks::ResourceMgr> _resource_mgr;
        std::shared_ptr<ks::GameWindow> _window;
        std::shared_ptr<ks::DataLoader> _data_loader;
        std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > > _units;

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
