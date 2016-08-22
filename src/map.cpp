#include "map.h"

namespace knights
{
    Map::Map(
        std::shared_ptr<knights::ResourceMgr> resource_mgr,
        std::string map_name
        )
        : _map_name(map_name),
          _resource_mgr(resource_mgr)
    {
        _tile_w = 32;
        _tile_h = 32;

        _tiles_cols = 70;
        _tiles_rows = 50;

        auto& r = _resource_mgr->get_spritesheet("knights_archer_walk");

        std::vector<int> frames = {10, 11
                                   , 12, 13, 14, 15, 16, 17
        };

        _animation = std::make_shared<knights::Animation>(
            r, frames
            );

        _animation->set_speed(0.5);
        _animation->play();

        for (int r = 0; r < _tiles_rows; r++) {
            for (int c = 0; c < _tiles_cols; c++) {
                auto s = _resource_mgr->get_spritesheet("tiles")
                    .get(0, 4);

                _tiles.push_back(
                    std::make_unique<knights::Tile>(
                        s,
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
        _animation->update(delta);
    }

    void
    Map::render(sf::RenderWindow& window)
    {
        // for (int s = 0; s < _sprites.size(); s++) {
        //     _sprites[s].setPosition(
        //         s % _tiles_rows * 32,
        //         s / _tiles_cols * 32
        //     );
        // }

        for (auto& tile : _tiles) {
            // tile->render(window);
        }

        _animation->render(window);
    }

    void
    Map::_init_map() const
    {

    }
}
