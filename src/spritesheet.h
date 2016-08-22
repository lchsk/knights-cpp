#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <memory>

#include <SFML/Graphics.hpp>

namespace ks
{
    class Spritesheet
    {
    public:
        Spritesheet(
            std::string path,
            int tile_width,
            int tile_height
        );
        ~Spritesheet();

        sf::Sprite get(int row, int col);

        /* Texture size in tiles */
        const sf::Vector2u& get_size();

    private:
        std::unique_ptr<sf::Texture> _texture;
        std::string _path;
        int _tile_width;
        int _tile_height;

        sf::Vector2u _tiles_n;
    };
}

#endif
