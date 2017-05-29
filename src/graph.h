#ifndef GRAPH_H
#define GRAPH_H

#include <memory>

#include <SFML/Graphics.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

/* #define DEBUG_GRAPH */

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

    typedef boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::undirectedS,
        std::shared_ptr<ks::Vertex>,
        boost::property<boost::edge_weight_t, double> > graph_t;

    typedef graph_t::edge_descriptor Edge;

    typedef boost::graph_traits<ks::graph_t>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<ks::graph_t>::edge_descriptor edge_t;

    class TileInfo
    {
    public:
    TileInfo(const int spritesheet_id, const int tile_id) :
        spritesheet_id(spritesheet_id), tile_id(tile_id)
        {
        }
        ~TileInfo(){};

        int spritesheet_id;
        int tile_id;

        bool operator==(const ks::TileInfo &other) const
        {
            return (spritesheet_id == other.spritesheet_id
                    && tile_id == other.tile_id);
        }
    };

    class TileMovement
    {
    public:
    TileMovement(const ks::TileInfo from, const ks::TileInfo to) :
        from(from), to(to){}
        ~TileMovement(){};

        bool operator==(const ks::TileMovement &other) const
        {
            return (from == other.from && to == other.to);
        }


        ks::TileInfo from;
        ks::TileInfo to;
    };

    class TileMovementHasher
    {
    public:
        std::size_t operator()(const ks::TileMovement& k) const
        {
            using std::size_t;
            using std::hash;

            return (
                hash<int>()(k.from.spritesheet_id)
                ^ (hash<int>()(k.from.tile_id) << 1)
                ^ hash<int>()(k.to.spritesheet_id)
                ^ (hash<int>()(k.to.tile_id) << 1));
        }
    };

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
        const std::shared_ptr<ks::Vertex>& get_vertex(const int v) const;
        const std::shared_ptr<ks::Vertex>&
            get_closest_vertex(const int x, const int y) const;

        const std::pair<ks::Edge, bool>
            get_edge(const int v1, const int v2) const;

        /* In pixels */
        const int get_rows() const;

        /* In pixels */
        const int get_cols() const;

        /* Number of vertex columns in the graph */
        const int get_vertex_cols() const;

        /* Number of vertices in the graph */
        const int get_vertex_count() const;

        const bool vertex_exists(const int v) const;
        const bool vertices_exist(const int v1, const int v2) const;

        const double get_weight(const ks::TileMovement& tile_mv);
        const double get_weight(const ks::Vertex& from,
                                const ks::Vertex& to);
        const double get_weight(const int from, const int to);

        /* Only applicable if an edge is part of the graph */
        const double get_weight_from_graph(const int v1, const int v2) const;

        void remove_edge(const int from, const int to);

        const std::unique_ptr<ks::Gps>& get_gps() const;

        void render(sf::RenderWindow& window);

    private:
        void _add_edge(const int v1, const int v2) const;

        std::unique_ptr<ks::graph_t> _graph;
        const std::unique_ptr<ks::Gps> _gps;

        #ifdef DEBUG_GRAPH
        std::vector<std::unique_ptr<sf::RectangleShape> > _debug_graph;
        #endif

        std::unordered_map<
            const ks::TileMovement,
            const double,
            ks::TileMovementHasher> _weights;

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

        inline const int get_direction(const int from, const int to)
        {
            if (is_right_col(from) && is_left_col(to)) return -1;
            if (is_left_col(from) && is_right_col(to)) return -1;
            if (is_top_row(from) && is_bottom_row(to)) return -1;
            if (is_bottom_row(from) && is_top_row(to)) return -1;

            if (from + 1 == to) return 1;
            if (from - 1 == to) return 3;
            if (from + v_col == to) return 2;
            if (from - v_col == to) return 0;

            return -1;
        }
    };

    std::vector<int> get_object_graph_ids(int x, int y, int w, int h, int cols,
                                          std::vector<int> offset);
}
#endif
