#include "level.h"

namespace ks
{
    Level::Level(std::shared_ptr<ks::ResourceMgr> resource_mgr,
                 std::shared_ptr<ks::DataLoader> data_loader)
        : _resource_mgr(resource_mgr),
          _data_loader(data_loader)
    {
        load_level_assets();
        init_nations();

        _map = std::make_unique<ks::Map>(
            resource_mgr,
            "test"
            );

        auto c_ptr = std::make_shared<ks::Character>(
            ks::NationType::Knights, "knights_archer", data_loader, resource_mgr);

        _characters.push_back(c_ptr);

    }

    Level::~Level()
    {

    }

    void
    Level::update(sf::Time delta)
    {
        _map->update(delta);

        for (auto& character : _characters) {
            character->update(delta);
        }

    }

    void
    Level::render(sf::RenderWindow& window)
    {
        _map->render(window, _characters);
    }

    void Level::init_nations()
    {

    }

    void Level::load_level_assets() const
    {
        _resource_mgr->load_texture(
            "tiles",
            "assets/images/knights_tiles.png"
            );
    }
}
