#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "../core/resource_mgr.h"
#include "../data/nation.h"

namespace knights
{
    namespace map
    {
        class Level : sf::NonCopyable
        {
            public:
                Level(std::shared_ptr<knights::res::ResourceMgr> resource_mgr);
                ~Level();

                void update(sf::Time delta);
                void render(sf::RenderWindow& window);

            private:
                std::unique_ptr<knights::map::Map> _map;
                std::shared_ptr<knights::res::ResourceMgr> _resource_mgr;

                void load_level_assets() const;
                void init_nations();
        };
    }
}

#endif
