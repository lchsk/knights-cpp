#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <memory>

#include <SFML/Graphics.hpp>

namespace knights
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

    private:
        std::unique_ptr<sf::Texture> _texture;
        std::string _path;
        int _tile_width;
        int _tile_height;
    };
}

#endif
