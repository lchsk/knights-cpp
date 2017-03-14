#include <iostream>

#include "graph.h"

namespace ks
{
    Graph::Graph()
        : _graph(std::make_unique<ks::graph_t>()),
          _gps(std::make_unique<ks::Gps>())
    {
    }

    Graph::~Graph()
    {
    }

    void Graph::init(const int rows, const int cols)
    {
        _rows = rows;
        _cols = cols;

        for (int r = 0; r < rows; r += 8) {
            for (int c = 0; c < cols; c += 8) {
                boost::add_vertex(
                    std::make_shared<ks::Vertex>(c, r, 0, 0), *_graph);
            }
        }

        _gps->v_cnt = boost::num_vertices(*_graph);
        _gps->v_col = _cols;

        for (int v = 0; v < _gps->v_cnt; v++) {
            _add_edge(v, _gps->get_n(v));
            _add_edge(v, _gps->get_e(v));
            _add_edge(v, _gps->get_s(v));
            _add_edge(v, _gps->get_w(v));
        }
    }

    void Graph::_add_edge(const int v1, const int v2) const
    {
        if (v2 < 0) return;

        auto edge = boost::edge(v1, v2, *_graph);

        if (edge.second) return;

        boost::add_edge(v1, v2, 1, *_graph);
    }

    const bool Graph::_is_connected(const int v1, const int v2) const
    {
        return boost::edge(v1, v2, *_graph).second;
    }
}
