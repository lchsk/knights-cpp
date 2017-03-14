#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "resource_mgr.h"
#include "animation.h"
#include "tile.h"
#include "unit.h"
#include "data_loader.h"
#include "game_window.h"
#include "graph.h"

namespace ks
{
    /* Side of each tile */
    const int TILE = 32;
    class Gps;

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
        std::unique_ptr<ks::Graph> _graph;

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

        /* Number of vertices in a column */
        int _v_col;

        /* Number of vertices per tile */
        const int _v_per_tile = 4;

        std::string _map_name;

        void _add_edge(const int v1, const int v2) const;
        void _build_initial_graph() const;

        bool _is_connected(const int v1, const int v2) const;

        std::unique_ptr<ks::Gps> _gps;

        // Debugging

        std::vector<std::unique_ptr<sf::RectangleShape> > _path;
    };

    class Gps {
    public:
        int v_col;
        int v_cnt;

        int get_nw(const int v) const
        {
            if (is_top_row(v) || is_left_col(v)) return -1;

            return v - v_col - 1;
        }

        int get_n(const int v) const
        {
            if (is_top_row(v)) return -1;

            return v - v_col;
        }

        int get_ne(const int v) const
        {
            if (is_top_row(v) || is_right_col(v)) return -1;

            return v - v_col + 1;
        }

        int get_e(const int v) const
        {
            if (is_right_col(v)) return -1;

            return v + 1;
        }

        int get_se(const int v) const
        {
            if (is_bottom_row(v) || is_right_col(v)) return -1;

            return v + v_col + 1;
        }

        int get_s(const int v) const
        {
            if (is_bottom_row(v)) return -1;

            return v + v_col;
        }

        int get_sw(const int v) const
        {
            if (is_bottom_row(v) || is_left_col(v)) return -1;

            return v + v_col - 1;
        }

        int get_w(const int v) const
        {
            if (is_left_col(v)) return -1;

            return v - 1;
        }

        bool is_top_row(const int v) const
        {
            return v < v_col;
        }

        bool is_bottom_row(const int v) const
        {
            return v >= v_cnt - v_col && v < v_cnt;
        }

        bool is_left_col(const int v) const
        {
            return v % v_col == 0;
        }

        bool is_right_col(const int v) const
        {
            return v % v_col == (v_col - 1);
        }
    };
}

#endif
