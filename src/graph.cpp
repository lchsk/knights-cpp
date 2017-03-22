#include <iostream>

#include "graph.h"

namespace ks
{
    Graph::Graph()
        : _graph(std::make_unique<ks::graph_t>()),
          _gps(std::make_unique<ks::Gps>()),
          _weights({
                  {ks::TileMovement(ks::TileInfo(0, 0), ks::TileInfo(0, 0)), 1}
              })
    {
    }

    Graph::~Graph()
    {
    }

    void Graph::init(
        const int rows,
        const int cols,
        std::map<std::pair<int, int>, std::vector<std::pair<int, int> > >&
        layers)
    {
        _rows = rows;
        _cols = cols;

        int id = 0;

        for (int r = 0; r < rows; r += 8) {
            for (int c = 0; c < cols; c += 8) {
                int tile_row = r / 32;
                int tile_col = c / 32;

                std::vector<std::pair<int, int> > tile
                    = layers[std::make_pair(tile_row, tile_col)];

                auto& top = tile[tile.size() - 1];

                boost::add_vertex(
                    std::make_shared<ks::Vertex>
                    (id++, c, r, top.first, top.second), *_graph);
            }
        }

        _gps->v_cnt = boost::num_vertices(*_graph);
        _gps->v_col = cols / 8;

        for (int v = 0; v < _gps->v_cnt; v++) {
            _add_edge(v, _gps->get_n(v));
            _add_edge(v, _gps->get_e(v));
            _add_edge(v, _gps->get_s(v));
            _add_edge(v, _gps->get_w(v));
        }
    }

    const bool Graph::is_connected(const int v1, const int v2) const
    {
        return boost::edge(v1, v2, *_graph).second;
    }

    const std::shared_ptr<ks::Vertex>& Graph::get_vertex(const int v) const
    {
        return (*_graph)[boost::vertex(v, *_graph)];
    }

    const std::unique_ptr<ks::Gps>& Graph::get_gps() const
    {
        return _gps;
    }

    const std::shared_ptr<ks::Vertex>&
    Graph::get_closest_vertex(const int x, const int y) const
    {
        const int v = y / 8 * _cols / 8 + x / 8;

        return get_vertex(v);
    }

    const double Graph::get_weight(const ks::TileMovement& tile_mv)
    {
        return _weights[tile_mv];
    }

    void Graph::find_path(std::shared_ptr<std::vector<ks::Vertex> >& path,
                          const int start_id, const int goal_id) const
    {
        vertex_t start = boost::vertex(start_id, *_graph);
        vertex_t goal = boost::vertex(goal_id, *_graph);

        std::vector<vertex_t> p(boost::num_vertices(*_graph));
        std::vector<int> d(boost::num_vertices(*_graph));

        auto pred_map = boost::make_iterator_property_map(
            p.begin(), boost::get(boost::vertex_index, *_graph));
        auto dist_map = boost::make_iterator_property_map(
            d.begin(), boost::get(boost::vertex_index, *_graph));
        // auto w_map = boost::get(&ks::edge_t, *_graph);
        // auto n_map = boost::get(&ks::vector_t, *_graph);

         boost::dijkstra_shortest_paths(
             *_graph, start,
              predecessor_map(pred_map).
             distance_map(dist_map));

        ks::vertex_t current = goal;

		bool path_found = true;

        while (current != start) {
            if (p[current] == current) {
                path_found = false;

                break;
            }

            auto vertex = (*_graph)[current];
            path->push_back(*vertex);

            current = p[current];
        }

        if (path_found) {
            auto vertex = (*_graph)[start];
            path->push_back(*vertex);
        } else {
            path->clear();
        }
    }

    void Graph::_add_edge(const int v1, const int v2) const
    {
        if (v2 < 0) {
            return;
        }

        auto edge = boost::edge(v1, v2, *_graph);

        // Edge already exists
        if (edge.second) {
            return;
        }

        auto V1 = get_vertex(v1);
        auto V2 = get_vertex(v2);

        auto weight = _weights.find(
            ks::TileMovement(
                ks::TileInfo(V1->spritesheet_id,
                             V1->tile_id),
                ks::TileInfo(V2->spritesheet_id,
                             V2->tile_id)));

        if (weight == _weights.end()) {
            return;
        }

        boost::add_edge(v1, v2, weight->second, *_graph);
    }
}
