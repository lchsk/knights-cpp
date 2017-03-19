#include "level.h"

namespace ks
{
    Level::Level(std::shared_ptr<ks::ResourceMgr>& resource_mgr,
                 std::shared_ptr<ks::DataLoader> data_loader,
                 std::shared_ptr<ks::GameWindow>& window)
        : _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _units(std::make_shared<std::vector<std::shared_ptr<ks::Unit> > >()),
          _selected(
              std::make_shared<std::vector<std::shared_ptr<ks::Unit> > >()),
          _window(window)
    {
        load_level_assets();
        init_nations();

        _unit_library = std::make_shared<ks::UnitLibrary>(resource_mgr);

        _map = std::make_shared<ks::Map>(
            resource_mgr,
            data_loader,
            window,
            _units,
            "map1.json");

        auto unit = std::make_shared<ks::Unit>(
            _unit_library->build_knights_archer()
        );
        auto unit2 = std::make_shared<ks::Unit>(
            _unit_library->build_knights_archer()
        );

        unit->set_position(0, 0);
        unit2->set_position(50, 60);

        _units->push_back(unit);
        _units->push_back(unit2);
    }

    Level::~Level()
    {

    }

    void Level::select_objects()
    {
        auto mouse_pos = sf::Mouse::getPosition(_window->get_window());

        bool new_selection = false;

        for (auto& unit : *_units) {
            if (unit->get_rectangle().contains(mouse_pos)) {
                new_selection = true;

                _selected->clear();
                _selected->push_back(unit);
            }
        }

        if (! new_selection && _selected->size() == 1) {
            // Move selected unit
            _map->move_unit((*_selected)[0], mouse_pos.x, mouse_pos.y);
        }
    }

    void Level::update(sf::Time delta)
    {
        _map->update(delta);

        for (auto& unit : *_units) {
            unit->update(delta);
        }
    }

    void Level::render(sf::RenderWindow& window)
    {
        _map->render(window);
    }

    void Level::init_nations()
    {

    }

    void Level::load_level_assets() const
    {
        // _resource_mgr->load_texture(
            // "tiles",
            // "assets/images/knights_tiles.png"
            // );
    }
}
