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
        boost::property<boost::edge_weight_t, int> > Graph;

    typedef boost::graph_traits<ks::Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<ks::Graph>::edge_descriptor edge_t;
}
#endif
