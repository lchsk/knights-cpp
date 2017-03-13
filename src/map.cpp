#include "map.h"

namespace ks
{
    Map::Map(
        std::shared_ptr<ks::ResourceMgr> resource_mgr,
        std::shared_ptr<ks::DataLoader> data_loader,
        std::shared_ptr<ks::GameWindow> window,
        std::string map_name)
        : _map_name(map_name),
          _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _window(window),
          _gps(std::make_unique<ks::Gps>()),
          _graph(std::make_unique<ks::Graph>())
    {
        load();
    }

    Map::~Map()
    {
    }

    void Map::load()
    {
        _data_loader->load_map(_map_name);
        json j_map = _data_loader->get_json(_map_name);

        _tiles_cols = j_map["metadata"]["columns"];
        _tiles_rows = j_map["metadata"]["rows"];

        _v_col = _tiles_cols * _v_per_tile;

        _window->set_map_size(ks::TILE * _tiles_cols, ks::TILE * _tiles_rows);

        std::vector<ks::Spritesheet*> spritesheets;

        // Names of spritesheets used in this map
        json j_sheets = j_map["spritesheets"];

        // Map data (tiles IDs)
        json j_data = j_map["data"];

        // List of layers to draw: layers are drawn from left to right
        json j_layers = j_map["draw_layers"];

        for (const std::string& spritesheet : j_sheets) {
            spritesheets.push_back(&_resource_mgr->get_spritesheet(spritesheet));
        }

        int row = 0;
        int col = 0;

        for (const std::string& layer : j_layers) {
            auto j_layer = j_data[layer];

            for (const auto& tile_info : j_layer) {
                // 0: spritesheet_id, 1: tile_id

                int c = col * ks::TILE;
                int r = row * ks::TILE;

                auto tile = std::make_unique<ks::Tile>(
                    spritesheets[tile_info[0]]->get_new_sprite(tile_info[1]),
                    c, r, tile_info[0], tile_info[1]);

                _tiles.push_back(std::move(tile));

                col++;

                if (col == _tiles_cols) {
                    col = 0;
                    row++;
                }

                if (row == _tiles_rows)
                    break;
            }
        }

        for (int R = 0; R < _tiles_rows * 4 * 8; R += 8) {
            for (int C = 0; C < _tiles_cols * 4 * 8; C += 8) {
                boost::add_vertex(
                    std::make_shared<ks::Vertex>(
                        C,
                        R,
                        0, 0), *_graph);
            }
        }

        _build_initial_graph();

		vertex_t s = boost::vertex(0, *_graph);
		vertex_t goal = boost::vertex(37, *_graph);

        auto ss = (*_graph)[0];
        auto gg = (*_graph)[37];

        std::vector<vertex_t> p(boost::num_vertices(*_graph));
        std::vector<int> d(boost::num_vertices(*_graph));

        dijkstra_shortest_paths(*_graph, s,
                                predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, *_graph))).
                                distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, *_graph))));

        std::vector<ks::vertex_t> path;
        ks::vertex_t current = goal;

        while (current != s) {
            path.push_back(current);

            current = p[current];
        }

        path.push_back(s);

        std::vector<boost::graph_traits<ks::Graph>::vertex_descriptor >::iterator it;

        for (it = path.begin(); it != path.end(); it++) {
            auto t = (*_graph)[*it];

            auto l = std::make_unique<sf::RectangleShape>();

            l->setFillColor(sf::Color::Red);
            l->setSize(sf::Vector2f(8, 8));
            l->setPosition(sf::Vector2f(t->x, t->y));

            _path.push_back(std::move(l));
        }
        std::cout << std::endl;
    }

    void Map::update(sf::Time delta)
    {
    }

    void Map::render(
        sf::RenderWindow& window,
        std::vector<std::shared_ptr<ks::Unit> >& units)
    {
        for (auto& tile : _tiles) {
            tile->render(window);
        }

        for (auto& unit : units) {
            unit->render(window);
        }

        for (auto& l : _path) {
            window.draw(*l);
        }
    }

    void Map::_add_edge(const int v1, const int v2) const
    {
        if (v2 < 0) return;

        auto edge = boost::edge(v1, v2, *_graph);

        if (edge.second) return;

        boost::add_edge(v1, v2, 1, *_graph);
    }

    bool Map::_is_connected(const int v1, const int v2) const
    {
        return boost::edge(v1, v2, *_graph).second;
    }

    void Map::_build_initial_graph() const
    {
        _gps->v_cnt = boost::num_vertices(*_graph);
        _gps->v_col = _v_col;

        for (int v = 0; v < _gps->v_cnt; v++) {
            _add_edge(v, _gps->get_nw(v));
            _add_edge(v, _gps->get_n(v));
            _add_edge(v, _gps->get_ne(v));
            _add_edge(v, _gps->get_e(v));
            _add_edge(v, _gps->get_se(v));
            _add_edge(v, _gps->get_s(v));
            _add_edge(v, _gps->get_sw(v));
            _add_edge(v, _gps->get_w(v));
        }
    }
}
