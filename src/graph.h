#ifndef GRAPH_H
#define GRAPH_H

#include <memory>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace ks
{
    class Vertex
    {
    public:
    Vertex(int x, int y, int spritesheet_id, int tile_id):
        x(x), y(y), spritesheet_id(spritesheet_id), tile_id(tile_id)
        {
        };

        int x;
        int y;
        int spritesheet_id;
        int tile_id;
    };

    class Edge
    {
    };

    typedef boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::undirectedS,
        std::shared_ptr<ks::Vertex>,
        boost::property<boost::edge_weight_t, int> > graph_t;

    typedef boost::graph_traits<ks::graph_t>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<ks::graph_t>::edge_descriptor edge_t;

    class Gps;

    class Graph
    {
    public:
        Graph();
        ~Graph();

        void init(const int rows, const int cols);

    private:
        void _add_edge(const int v1, const int v2) const;
        const bool _is_connected(const int v1, const int v2) const;

        std::unique_ptr<ks::graph_t> _graph;
        std::unique_ptr<ks::Gps> _gps;

        int _rows;
        int _cols;
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
