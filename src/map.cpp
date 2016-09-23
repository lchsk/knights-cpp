/*
Defines and draws current map - tiles
*/

#include "map.h"

namespace ks
{
    Map::Map(
        std::shared_ptr<ks::ResourceMgr> resource_mgr,
        std::shared_ptr<ks::DataLoader> data_loader,
        std::string map_name)
        : _map_name(map_name),
          _resource_mgr(resource_mgr)
    {
        _tile_w = 32;
        _tile_h = 32;

        json map = data_loader->load_map("map1.json");

        _tiles_cols = map["metadata"]["columns"];
        _tiles_rows = map["metadata"]["rows"];

        std::vector<ks::Spritesheet*> spritesheets;

        json j_sheets = map["spritesheets"];
        json j_data = map["data"];
        json j_land = j_data["land"];

        for (json::iterator it = j_sheets.begin(); it != j_sheets.end(); ++it) {
            spritesheets.push_back(&_resource_mgr->get_spritesheet(it.value()));
        }

        int r = 0;
        int c = 0;

        for (json::iterator it = j_land.begin(); it != j_land.end(); ++it) {
            auto item = it.value();

            int spritesheet_id = item[0];
            int tile_id = item[1];

            auto s = spritesheets[spritesheet_id]->get(tile_id);

            _tiles.push_back(
                    std::make_unique<ks::Tile>(
                        *s,
                        c * _tile_w,
                        r * _tile_h
                        )
                    );

            c++;

            if (c == _tiles_cols) {
                c = 0;
                r++;
            }
        }
    }

    Map::~Map()
    {

    }

    void
    Map::update(sf::Time delta)
    {
    }

    void
    Map::render(sf::RenderWindow& window,
                std::vector<std::shared_ptr<ks::Character> >& characters)
    {
        // for (int s = 0; s < _sprites.size(); s++) {
        //     _sprites[s].setPosition(
        //         s % _tiles_rows * 32,
        //         s / _tiles_cols * 32
        //     );
        // }

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
