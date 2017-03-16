#include "map.h"

namespace ks
{
    Map::Map(
        std::shared_ptr<ks::ResourceMgr>& resource_mgr,
        std::shared_ptr<ks::DataLoader>& data_loader,
        std::shared_ptr<ks::GameWindow>& window,
        std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > >& units,
        std::string map_name)
        : _map_name(map_name),
          _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _window(window),
          _units(units),
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

        for (const std::string& layer : j_layers) {
            auto j_layer = j_data[layer];

            int row = 0;
            int col = 0;

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

        _graph->init(_tiles_rows * ks::TILE, _tiles_cols * ks::TILE);

        // Find path:

        std::shared_ptr<std::vector<ks::Vertex> > path
            = std::make_shared<std::vector<ks::Vertex> >();

        _graph->find_path(path, 0, 60);

        (*_units)[0]->set_path(path);
    }

    void Map::update(sf::Time delta)
    {
    }

    void Map::render(sf::RenderWindow& window)
    {
        for (auto& tile : _tiles) {
            tile->render(window);
        }

        for (auto& unit : *_units) {
            unit->render(window);
        }
    }
}
