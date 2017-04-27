#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "resource_mgr.h"
#include "nation.h"
#include "data_loader.h"
#include "game_window.h"
#include "unit_template.h"
#include "unit_library.h"
#include "unit.h"
#include "object_template.h"
#include "object_library.h"
#include "object.h"

namespace ks
{
    class Level : sf::NonCopyable
    {
    public:
        Level(
            std::shared_ptr<ks::ResourceMgr>& resource_mgr,
            std::shared_ptr<ks::DataLoader> data_loader,
            std::shared_ptr<ks::GameWindow>& window
        );
        ~Level();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        void select_objects();

    private:
        std::shared_ptr<ks::Map> _map;
        std::shared_ptr<ks::ResourceMgr> _resource_mgr;
        std::shared_ptr<ks::DataLoader> _data_loader;
        std::shared_ptr<ks::GameWindow> _window;
        std::shared_ptr<ks::UnitLibrary> _unit_library;
        std::shared_ptr<ks::ObjectLibrary> _object_library;

        std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > > _units;
        std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > > _selected;
        std::shared_ptr<std::vector<std::shared_ptr<ks::Object> > > _objects;

        void load_level_assets() const;
        void init_nations();
    };
}

#endif
