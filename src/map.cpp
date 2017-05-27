#include "map.h"
#include "util.h"

namespace ks
{
    Map::Map(
        std::shared_ptr<ks::ResourceMgr>& resource_mgr,
        std::shared_ptr<ks::DataLoader>& data_loader,
        std::shared_ptr<ks::GameWindow>& window,
        std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > >& units,
        std::shared_ptr<std::vector<std::shared_ptr<ks::Object> > >& objects,
        std::shared_ptr<std::vector<std::shared_ptr<ks::MapObject> > >&
        map_objects,
        std::string map_name)
        : _map_name(map_name),
          _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _window(window),
          _units(units),
          _objects(objects),
          _map_objects(map_objects),
          _graph(std::make_unique<ks::Graph>())
    {
        load();
    }

    Map::~Map()
    {
    }

    void Map::set_position(const std::shared_ptr<ks::Unit>& unit,
                           const int v) const
    {
        const auto& vertex = _graph->get_vertex(v);

        unit->set_position(vertex->x, vertex->y);
    }

    void Map::load()
    {
        _data_loader->load_map(_map_name);
        json j_map = _data_loader->get_json(_map_name);

        _tiles_cols = j_map["metadata"]["columns"];
        _tiles_rows = j_map["metadata"]["rows"];

        _window->set_map_size(ks::TILE_SIZE * _tiles_cols,
                              ks::TILE_SIZE * _tiles_rows);

        std::vector<ks::Spritesheet*> spritesheets;

        // Names of spritesheets used in this map
        json j_sheets = j_map["spritesheets"];

        // Map data (tiles IDs)
        json j_data = j_map["data"];

        // List of layers to draw: layers are drawn from left to right
        json j_layers = j_map["draw_layers"];

        for (const std::string& spritesheet : j_sheets) {
            spritesheets.push_back(&_resource_mgr->get_spritesheet(spritesheet));
        }

        std::map<std::pair<int, int>, std::vector<std::pair<int, int> > >
            layers;

        for (const std::string& layer : j_layers) {
            auto j_layer = j_data[layer];

            int row = 0;
            int col = 0;

            for (const auto& tile_info : j_layer) {
                // 0: spritesheet_id, 1: tile_id

                int c = col * ks::TILE_SIZE;
                int r = row * ks::TILE_SIZE;

                auto tile = std::make_unique<ks::Tile>(
                    spritesheets[tile_info[0]]->get_new_sprite(tile_info[1]),
                    c, r, tile_info[0], tile_info[1]);

                layers[std::make_pair(row, col)].push_back(
                    std::make_pair(tile_info[0], tile_info[1]));

                _tiles.push_back(std::move(tile));

                col++;

                if (col == _tiles_cols) {
                    col = 0;
                    row++;
                }

                if (row == _tiles_rows)
                    break;
            }
        }

        _graph->init(_tiles_rows * ks::TILE_SIZE,
                     _tiles_cols * ks::TILE_SIZE,
                     layers);
    }

    void Map::move_unit(
        const std::shared_ptr<ks::Unit>& unit,
        const int x,
        const int y) const
    {
        std::shared_ptr<std::vector<ks::Vertex> > path
            = std::make_shared<std::vector<ks::Vertex> >();

        sf::Vector2f current_pos;
        std::shared_ptr<ks::Vertex> from;

        if (unit->is_walking()) {
            from = std::make_shared<ks::Vertex>(unit->get_current_target());
        } else {
            current_pos = unit->get_position();
            from = _graph->get_closest_vertex(current_pos.x, current_pos.y);
        }

        const auto& to = _graph->get_closest_vertex(x, y);

        _graph->find_path(path, from->id, to->id);

        if (path->size())
            unit->set_path(path);
    }

    void Map::update(sf::Time delta)
    {
        std::sort(_map_objects->begin(), _map_objects->end(),
                  map_object_y_pos_sorter);

        for (auto& map_object : *_map_objects) {
            map_object->update(delta);

            if (map_object->is_walking()) {
                _move_unit_step(std::dynamic_pointer_cast<ks::Unit>(map_object),
                                delta);
            }
        }
    }

    void Map::render(sf::RenderWindow& window)
    {
        for (auto& tile : _tiles) {
            tile->render(window);
        }

        for (auto& map_object : *_map_objects) {
            map_object->render(window);
        }

        _graph->render(window);
    }

    void Map::add_object(const std::shared_ptr<ks::Object>& obj)
    {
        const auto obj_pos = obj->get_current_animation()->get_position();

        const sf::Vector2i obj_size = obj->get_current_animation()->get_size();
        const sf::Vector2i obj_size_tiles
            = obj->get_current_animation()->get_size_tiles();

        std::vector<int> object_graph_ids
            = get_object_graph_ids(obj_pos.y,
                                   obj_pos.x,
                                   obj_size.x,
                                   obj_size.y,
                                   _graph->get_vertex_cols(),
                                   // TODO: Get object's offset
                                   {});

        assert(object_graph_ids.size() == obj_size_tiles.x * obj_size_tiles.y);

        for (const int gid : object_graph_ids) {
            const auto& gps = _graph->get_gps();

            std::vector<int> dirs = {
                gps->get_w(gid),
                gps->get_s(gid),
                gps->get_e(gid),
                gps->get_n(gid),
            };

            for (int j : dirs) {
                if (j != -1 && _graph->is_connected(j, gid)) {
                    _graph->remove_edge(gid, j);
                }
            }
        }
    }

    void Map::_move_unit_step(
        const std::shared_ptr<ks::Unit>& unit, sf::Time& delta)
    {
        const auto& path = unit->get_path();

        if (path->size() < 2) return;

        auto v = (*path)[0];
        auto next_v = (*path)[1];

        int dir = _graph->get_gps()->get_direction(v.id, next_v.id);

        const double speed_factor = _graph->get_weight(v, next_v);

        const int speed = unit->get_template()->get_speed() * 1 / speed_factor;

        const auto& pos = unit->get_position();

        double step_x = 0;
        double step_y = 0;

        double x = pos.x;
        double y = pos.y;

        const double step = speed * delta.asSeconds();

        bool arrived = false;

        switch (dir) {
        case 0:
            step_y = -step;
            unit->set_animation("walk_up");
            arrived = y + step_y < next_v.y + 1;

            break;
        case 2:
            step_y = step;
            unit->set_animation("walk_down");
            arrived = y + step_y > next_v.y - 1;

            break;
        case 1:
            step_x = step;
            unit->set_animation("walk_right");
            arrived = x + step_x > next_v.x - 1;

            break;
        case 3:
            step_x = -step;
            unit->set_animation("walk_left");
            arrived = x + step_x < next_v.x + 1;

            break;
        }

        switch(dir) {
        case 1:
        case 3:
            if (arrived) {
                x = next_v.x;

                unit->pop_path_step();
            } else {
                x += step_x;
            }

            break;

        case 0:
        case 2:
            if (arrived) {
                y = next_v.y;

                unit->pop_path_step();
            } else {
                y += step_y;
            }

            break;
        }

        unit->set_position(x, y);

        if (path->size() == 1) {
            // Path finished

            switch (dir) {
            case 0:
                unit->set_animation("stand_up");
                break;
            case 2:
                unit->set_animation("stand_down");
                break;
            case 1:
                unit->set_animation("stand_right");
                break;
            case 3:
                unit->set_animation("stand_left");
                break;
            }

            unit->clear_path();
        }
    }
}
