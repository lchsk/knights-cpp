/*
Defines and draws current map - tiles
*/

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
          _window(window)
    {
        load();
    }

    Map::~Map()
    {

    }

    void Map::load()
    {
        json j_map = _data_loader->load_map(_map_name);

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

        int row = 0;
        int col = 0;

        for (const std::string& layer : j_layers) {
            auto j_layer = j_data[layer];

            for (const auto& tile_info : j_layer) {
                // 0: spritesheet_id, 1: tile_id
                auto tile = spritesheets[tile_info[0]]->get(tile_info[1]);

                _tiles.push_back(std::make_unique<ks::Tile>(
                                 *tile,
                                 col * ks::TILE,
                                 row * ks::TILE
                                 ));

                col++;

                if (col == _tiles_cols) {
                    col = 0;
                    row++;
                }

                if (row == _tiles_rows)
                    break;
            }
        }

    }

    void
    Map::update(sf::Time delta)
    {
    }

    void
    Map::render(sf::RenderWindow& window,
                std::vector<std::shared_ptr<ks::Character> >& characters)
    {
        for (auto& tile : _tiles) {
            tile->render(window);
        }

        for (auto& character : characters) {
            character->render(window);
        }
    }

    void
    Map::_init_map() const
    {

    }
}
