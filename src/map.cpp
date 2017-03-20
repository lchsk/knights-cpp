#include "map.h"

namespace ks
{
    Map::Map(
        std::shared_ptr<ks::ResourceMgr>& resource_mgr,
        std::shared_ptr<ks::DataLoader>& data_loader,
        std::shared_ptr<ks::GameWindow>& window,
        std::shared_ptr<std::vector<std::shared_ptr<ks::Unit> > >& units,
        std::string map_name)
        : _map_name(map_name),
          _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _window(window),
          _units(units),
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

        _window->set_map_size(ks::TILE * _tiles_cols, ks::TILE * _tiles_rows);

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

                int c = col * ks::TILE;
                int r = row * ks::TILE;

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

        _graph->init(_tiles_rows * ks::TILE, _tiles_cols * ks::TILE,
            layers);
    }

    void Map::move_unit(
        const std::shared_ptr<ks::Unit>& unit,
        const int x,
        const int y) const
    {
        std::shared_ptr<std::vector<ks::Vertex> > path
            = std::make_shared<std::vector<ks::Vertex> >();

        const sf::Vector2f current_pos = unit->get_position();

        const auto& from = _graph->get_closest_vertex(
            current_pos.x, current_pos.y);
        const auto& to = _graph->get_closest_vertex(x, y);

        _graph->find_path(path, from->id, to->id);

        unit->set_path(path);
    }

    void Map::update(sf::Time delta)
    {
        std::sort(_units->begin(), _units->end(), y_coord_pred);

        for (auto& unit : *_units) {
            unit->update(delta);

            if (unit->is_walking()) {
                _move_unit_step(unit, delta);
            }
        }
    }

    void Map::render(sf::RenderWindow& window)
    {
        for (auto& tile : _tiles) {
            tile->render(window);
        }

        for (auto& unit : *_units) {
            unit->render(window);
        }
    }

    void Map::_move_unit_step(
        const std::shared_ptr<ks::Unit>& unit, sf::Time& delta)
    {
        const auto& path = unit->get_path();

        if (path->size() < 2) return;

        auto v = (*path)[0];
        auto next_v = (*path)[1];

        int dir = get_direction(v.id, next_v.id);

        auto mv = ks::TileMovement(
            ks::TileInfo(v.spritesheet_id, v.tile_id),
            ks::TileInfo(next_v.spritesheet_id, next_v.tile_id));

        const double speed_factor = _graph->get_weight(mv);

        const int speed = unit->get_template()->get_speed() * speed_factor;

        const auto& pos = unit->get_position();

        double x = pos.x;
        double y = pos.y;

        switch (dir) {
        case 0:
            y -= speed * delta.asSeconds();
            unit->set_animation("walk_up");
            break;
        case 2:
            y += speed * delta.asSeconds();
            unit->set_animation("walk_down");
            break;
        case 1:
            x += speed * delta.asSeconds();
            unit->set_animation("walk_right");
            break;
        case 3:
            x -= speed * delta.asSeconds();
            unit->set_animation("walk_left");
            break;
        }

        unit->set_position(x, y);

        if ((dir == 1 || dir == 3) && fabs(next_v.x - x) < 0.5) {
            x = next_v.x;
            unit->pop_path_step();
        } else if ((dir == 0 || dir == 2) && fabs(next_v.y - y) < 0.5) {
            y = next_v.y;
            unit->pop_path_step();
        }

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
