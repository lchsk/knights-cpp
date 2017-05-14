#include <iostream>

#include "graph.h"
#include "util.h"

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

        for (int r = 0; r < rows; r += ks::PX_PER_V) {
            for (int c = 0; c < cols; c += ks::PX_PER_V) {
                int tile_row = r / ks::TILE_SIZE;
                int tile_col = c / ks::TILE_SIZE;

                std::vector<std::pair<int, int> > tile
                    = layers[std::make_pair(tile_row, tile_col)];

                auto& top = tile[tile.size() - 1];

                boost::add_vertex(
                    std::make_shared<ks::Vertex>
                    (id++, c, r, top.first, top.second), *_graph);
            }
        }

        _gps->v_cnt = boost::num_vertices(*_graph);
        _gps->v_col = cols / ks::PX_PER_V;

        for (int v = 0; v < _gps->v_cnt; v++) {
            _add_edge(v, _gps->get_n(v));
            _add_edge(v, _gps->get_e(v));
            _add_edge(v, _gps->get_s(v));
            _add_edge(v, _gps->get_w(v));
        }

        #ifdef DEBUG_GRAPH
        for (int v = 0; v < _gps->v_cnt - 1; v++) {
            const auto& from = get_vertex(v);
            const auto& to = get_vertex(v + 1);

            const std::vector<int> neighbors = {
                _gps->get_e(v),
                _gps->get_s(v),
                _gps->get_w(v),
                _gps->get_n(v)
            };

            for (int n = 0; n < neighbors.size(); n++) {
                const int v2 = neighbors[n];

                if (v2 == -1) continue;

                const double weight = get_weight(v, v2);

                auto shape = std::make_unique<sf::RectangleShape>();

                if (weight) {
                    shape->setFillColor(DebugGreen);
                } else {
                    shape->setFillColor(DebugRed);
                }

                shape->setSize(sf::Vector2f(4, 4));

                const int x1 = std::min(from->x, to->x);
                const int x2 = std::max(from->x, to->x);
                const int y1 = std::min(from->y, to->y);
                const int y2 = std::max(from->y, to->y);

                int x, y;

                x = x1 + x2 / 2.0;
                y = y1 + y2 / 2.0;

                shape->setPosition(sf::Vector2f(from->x + 6, from->y + 6));

                _debug_graph.push_back(std::move(shape));
            }
        }
        #endif
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
        const int v = y / ks::PX_PER_V
            * _cols / ks::PX_PER_V + x / ks::PX_PER_V;

        return get_vertex(v);
    }

    const double Graph::get_weight(const ks::TileMovement& tile_mv)
    {
        return _weights[tile_mv];
    }

    const double Graph::get_weight(const ks::Vertex& from,
                                   const ks::Vertex& to)
    {
        const auto mv = ks::TileMovement(
            ks::TileInfo(from.spritesheet_id, from.tile_id),
            ks::TileInfo(to.spritesheet_id, to.tile_id));

        return get_weight(mv);
    }

    const double Graph::get_weight(const int from, const int to)
    {
        auto& f = get_vertex(from);
        auto& t = get_vertex(to);

        return get_weight(*f, *t);
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

    void Graph::render(sf::RenderWindow& window)
    {
        #ifdef DEBUG_GRAPH
        for (auto& v : _debug_graph) {
            window.draw(*v);
        }
        #endif
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

    std::vector<int> get_object_graph_ids(int r, int c, int w, int h, int cols)
    {
        assert(r);
        assert(c);
        assert(w);
        assert(h);
        assert(cols);

        std::vector<int> ids;

        const int left_node = floor(c / 8.0);
        const int top_node = floor(r / 8.0);

        const int start_node = top_node * cols + left_node;

        const int width = ceil(w / 8.0);
        const int height = ceil(h / 8.0);

        // std::cout << "\tleft_node: " << left_node
                  // << "\ttop_node:"   << top_node
                  // << "\twidth:"      << width
                  // << "\theight:"     << height
                  // << "\n";

        for (int n1 = start_node, i = 0; i < height; n1 += cols, i++) {
            for (int n2 = n1, j = 0; j < width; n2++, j++) {
                ids.push_back(n2);
            }
        }

        return ids;
    }
}
