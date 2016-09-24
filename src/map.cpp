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

        json j_sheets = j_map["spritesheets"];
        json j_data = j_map["data"];
        json j_land = j_data["land"];

        for (json::iterator it = j_sheets.begin(); it != j_sheets.end(); ++it) {
            spritesheets.push_back(&_resource_mgr->get_spritesheet(it.value()));
        }

        int row = 0;
        int col = 0;

        for (json::iterator it = j_land.begin(); it != j_land.end(); ++it) {
            auto item = it.value();

            auto tile = spritesheets[item[0]]->get(item[1]);

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
