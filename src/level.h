#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "resource_mgr.h"
#include "nation.h"

namespace ks
{
    class Level : sf::NonCopyable
    {
    public:
        Level(std::shared_ptr<ks::ResourceMgr> resource_mgr);
        ~Level();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

    private:
        std::unique_ptr<ks::Map> _map;
        std::shared_ptr<ks::ResourceMgr> _resource_mgr;

        void load_level_assets() const;
        void init_nations();
    };
}

#endif