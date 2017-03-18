#ifndef GRAPH_H
#define GRAPH_H

#include <memory>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace ks
{
    class Vertex
    {
    public:
    Vertex(int id, int x, int y, int spritesheet_id, int tile_id):
        id(id), x(x), y(y), spritesheet_id(spritesheet_id), tile_id(tile_id)
        {
        };

        int id;
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

        void init(
            const int rows,
            const int cols,
            std::map<std::pair<int, int>, std::vector<std::pair<int, int> > >&
            layers);

        void find_path(std::shared_ptr<std::vector<ks::Vertex> >& path,
                       const int start_id, const int goal_id) const;

        const bool is_connected(const int v1, const int v2) const;

    private:
        void _add_edge(const int v1, const int v2, const int weight) const;

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

    inline const int get_direction(const int from, const int to)
    {
        int col = 256 / 8;

        if ((from + 1) == to) return 1;
        if ((from - 1) == to) return 3;
        if ((from + col) == to) return 2;
        if ((from - col) == to) return 0;

        return -1;
    }
}
#endif
