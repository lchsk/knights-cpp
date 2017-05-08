#include "spritesheet.h"
#include "util.h"

namespace ks
{
    Spritesheet::Spritesheet(
        std::string path,
        const json& j_data,
        int tile_width,
        int tile_height
    ) :
        _path(path),
        _tile_width(tile_width),
        _tile_height(tile_height)
    {
        _insert_tile_info(j_data);

        _texture = std::make_unique<sf::Texture>();

        if (! _texture->loadFromFile(_path)) {
            throw std::runtime_error("Unable to load " + _path);
        }

        auto texture_size = _texture->getSize();

        _cols = texture_size.x / tile_width;
        _rows = texture_size.y / tile_height;
    }

    Spritesheet::~Spritesheet()
    {
    }

    std::unique_ptr<sf::Sprite> Spritesheet::get_new_sprite(int frame)
    {
        return std::make_unique<sf::Sprite>(*_texture.get(), _get_rect(frame));
    }

    std::unique_ptr<sf::Sprite> Spritesheet::get_new_sprite(sf::IntRect& r)
    {
        return std::make_unique<sf::Sprite>(*_texture.get(), r);
    }

    const std::unique_ptr<sf::Texture>& Spritesheet::get_texture() const
    {
        return _texture;
    }

    // void Spritesheet::set_position(double x, double y)
    // {
        // const auto& pos = sf::Vector2f(x, y);

        // for (auto& sprite : _sprites) {
            // sprite->setPosition(pos);
        // }
    // }

    void Spritesheet::_insert_tile_info(const json& j_data)
    {
        if (j_data != nullptr) {
            for (auto const& tile_info : j_data["data"]) {
                int id = tile_info["id"];

                // std::cout << "Add tileinfo " << id << "\n";

                // _tiles_info[id] = std::make_shared<TileInfo>(id);
            }
        }
    }

    sf::IntRect Spritesheet::_get_rect(int frame)
    {
        return sf::IntRect(
            get_col(frame, _cols) * _tile_width,
            get_row(frame, _cols) * _tile_height,
            _tile_width, _tile_height);
    }
}
