#include "spritesheet.h"
#include "util.h"

namespace ks
{
    Spritesheet::Spritesheet(std::string path, int tile_width, int tile_height)
        : _path(path),
          _tile_width(tile_width),
          _tile_height(tile_height),
          _type(SpritesheetType::Grid)
    {
        _texture = std::make_unique<sf::Texture>();

        if (! _texture->loadFromFile(_path)) {
            throw std::runtime_error("Unable to load " + _path);
        }

        auto texture_size = _texture->getSize();

        _cols = texture_size.x / tile_width;
        _rows = texture_size.y / tile_height;
    }

    Spritesheet::Spritesheet(std::string path, const json& data)
        : _path(path),
          _type(SpritesheetType::Named)
    {
        _texture = std::make_unique<sf::Texture>();

        if (! _texture->loadFromFile(_path)) {
            throw std::runtime_error("Unable to load " + _path);
        }

        _load_desc(data);
    }

    Spritesheet::~Spritesheet()
    {
    }

    std::unique_ptr<sf::Sprite> Spritesheet::get_new_sprite(int frame)
    {
        if (_type == SpritesheetType::Named) {
            return get_new_sprite(_desc_frames[frame]);
        }

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

    void Spritesheet::_load_desc(const json& desc)
    {
        if (desc == nullptr)
            return;

        for (auto const& tile : desc) {
            const sf::IntRect r = sf::IntRect(tile["x"],
                                              tile["y"],
                                              tile["w"],
                                              tile["h"]);

            const std::string s = tile["params"]["id"];
            const int id = std::atoi(s.c_str());

            _desc[tile["name"]] = r;
            _desc_frames[id] = r;
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
