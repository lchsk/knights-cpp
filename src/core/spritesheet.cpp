#include "spritesheet.h"

namespace knights
{
    Spritesheet::Spritesheet(
        std::string path,
        int tile_width,
        int tile_height
    ) :
        _path(path),
        _tile_width(tile_width),
        _tile_height(tile_height)
    {
        _texture = std::make_unique<sf::Texture>();

        if (! _texture->loadFromFile(_path)) {
            throw std::runtime_error("Unable to load " + _path);
        }
    }

    Spritesheet::~Spritesheet()
    {
    }

    sf::Sprite
    Spritesheet::get(int row, int col)
    {
        return sf::Sprite(
            *_texture.get(),
            sf::IntRect(
                col * _tile_height,
                row * _tile_width,
                _tile_height,
                _tile_width
            )
        );
    }

}
