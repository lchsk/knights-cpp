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

        _tiles_cols = 70;
        _tiles_rows = 50;

        json map = data_loader->load_map("map1.json");

        for (int r = 0; r < _tiles_rows; r++) {
            for (int c = 0; c < _tiles_cols; c++) {
                auto s = _resource_mgr->get_spritesheet("tiles")
                    .get(0, 4);

                _tiles.push_back(
                    std::make_unique<ks::Tile>(
                        *s,
                        r * _tile_w,
                        c * _tile_h
                        )
                    );
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
