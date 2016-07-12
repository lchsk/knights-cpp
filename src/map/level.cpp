#include "level.h"

namespace knights
{
    namespace map
    {
        Level::Level(std::shared_ptr<knights::res::ResourceMgr> resource_mgr)
            : _resource_mgr(resource_mgr)
        {
            load_level_assets();

            _map = std::unique_ptr<knights::map::Map>(
                new knights::map::Map(
                resource_mgr,
                "test"
            ));
        }

        Level::~Level()
        {

        }

        void
        Level::update(sf::Time delta)
        {
            _map->update(delta);
        }

        void
        Level::render(sf::RenderWindow& window)
        {
            _map->render(window);
        }

        void Level::load_level_assets() const
        {
            _resource_mgr->load_texture(
                "tiles",
                "assets/images/knights_tiles.png"
            );
        }
    }
}
