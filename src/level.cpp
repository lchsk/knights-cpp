#include "level.h"

namespace ks
{
    Level::Level(std::shared_ptr<ks::ResourceMgr> resource_mgr,
                 std::shared_ptr<ks::DataLoader> data_loader,
                 std::shared_ptr<ks::GameWindow> window)
        : _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _window(window)
    {
        load_level_assets();
        init_nations();
        units::init_units();

        _map = std::make_unique<ks::Map>(
            resource_mgr,
            data_loader,
            window,
            "map1.json"
            );

        auto unit = std::make_shared<ks::Unit>(
            ks::NationType::Knights,
            "knights_archer",
            data_loader,
            resource_mgr
        );

        _units.push_back(unit);

    }

    Level::~Level()
    {

    }

    void Level::select_objects()
    {
        auto mouse_pos = sf::Mouse::getPosition(_window->get_window());

        // std::cout << mouse_pos.x << "\n";

        for (auto& unit : _units) {

        }


    }

    void Level::update(sf::Time delta)
    {
        _map->update(delta);

        for (auto& unit : _units) {
            unit->update(delta);
        }
    }

    void Level::render(sf::RenderWindow& window)
    {
        _map->render(window, _units);
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
