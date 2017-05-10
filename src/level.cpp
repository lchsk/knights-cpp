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
          _objects(
              std::make_shared<std::vector<std::shared_ptr<ks::Object> > >()),
          _map_objects(
              std::make_shared<std::vector<std::shared_ptr<ks::MapObject> > >()),
          _window(window)
    {
        load_level_assets();
        init_nations();

        _unit_library = std::make_shared<ks::UnitLibrary>(resource_mgr);
        _object_library = std::make_shared<ks::ObjectLibrary>(resource_mgr);

        _map = std::make_shared<ks::Map>(
            resource_mgr,
            data_loader,
            window,
            _units,
            _objects,
            _map_objects,
            "map1.json");

        auto unit = std::make_shared<ks::Unit>(
            _unit_library->build_knights_archer()
        );
        auto unit2 = std::make_shared<ks::Unit>(
            _unit_library->build_knights_archer()
        );

        unit->set_position(0, 0);
        unit2->set_position(50, 60);

        _map_objects->push_back(unit);
        _map_objects->push_back(unit2);

        auto tree = std::make_shared<ks::Object>(_object_library->build_tree());

        // tree->set_position(0, 0);

        _map_objects->push_back(tree);
    }

    Level::~Level()
    {

    }

    void Level::select_objects()
    {
        auto mouse_pos = sf::Mouse::getPosition(_window->get_window());

        const auto top_left = _window->get_top_left();
        mouse_pos.x += top_left.x;
        mouse_pos.y += top_left.y;

        bool new_selection = false;

        for (auto& map_object : *_map_objects) {
            if (map_object->get_type() == ks::MapObjectType::Unit
                && map_object->get_rectangle().contains(mouse_pos)) {
                new_selection = true;

                _selected->clear();
                _selected->push_back(std::dynamic_pointer_cast
                                     <ks::Unit>(map_object));
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
