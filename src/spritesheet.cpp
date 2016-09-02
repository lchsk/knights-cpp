#include "spritesheet.h"

namespace ks
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

        auto texture_size = _texture->getSize();

        // Columns
        _tiles_n.x = texture_size.x / tile_width;

        // Rows
        _tiles_n.y = texture_size.y / tile_height;

        for (int row = 0; row < _tiles_n.y; row++) {
            for (int col = 0; col < _tiles_n.x; col++) {
                _sprites.push_back(
                    std::make_unique<sf::Sprite>(
                        *_texture.get(),
                        sf::IntRect(
                            col * _tile_height,
                            row * _tile_width,
                            _tile_height,
                            _tile_width
                            )
                        )
                    );
            }
        }
    }

    Spritesheet::~Spritesheet()
    {
    }

    sf::Sprite Spritesheet::get(int row, int col)
    {
        return *_sprites[row * _tiles_n.x + col];
    }

    sf::Sprite
    Spritesheet::get(int frame)
    {
        return *_sprites[frame];
        // return sf::Sprite(
        //     *_texture.get(),
        //     sf::IntRect(
        //         col * _tile_height,
        //         row * _tile_width,
        //         _tile_height,
        //         _tile_width
        //     )
        // );
    }

    const sf::Vector2u&
    Spritesheet::get_size()
    {
        return _tiles_n;
    }
}
