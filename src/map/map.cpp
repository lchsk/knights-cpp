#include "map.h"

namespace knights
{
    namespace map
    {
        Map::Map(
            std::shared_ptr<knights::res::ResourceMgr> resource_mgr,
            std::string map_name
        )
            : _map_name(map_name),
              _resource_mgr(resource_mgr)
        {
            _tile_w = 32;
            _tile_h = 32;

            _tiles_cols = 70;
            _tiles_rows = 50;

            for (int r = 0; r < _tiles_rows; r++) {
                for (int c = 0; c < _tiles_cols; c++) {
                    auto s = _resource_mgr->get_spritesheet("tiles")
                        .get(0, 4);

                    // auto s = sf::Sprite(
                    //     _resource_mgr->get_texture("tiles"),
                    //     sf::IntRect(0, 0, 32, 32)
                    // );
                    _sprites.push_back(s);
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
        Map::render(sf::RenderWindow& window)
        {
            for (int s = 0; s < _sprites.size(); s++) {
                _sprites[s].setPosition(
                    s % _tiles_rows * 32,
                    s / _tiles_cols * 32
                );

                window.draw(_sprites[s]);
            }

        }

        void
        Map::_init_map() const
        {

        }
    }
}
