#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <memory>
#include <unordered_map>

#include "../thirdparty/json/src/json.hpp"

#include <SFML/Graphics.hpp>

using json = nlohmann::json;

namespace ks
{
    class Spritesheet
    {
    public:
        Spritesheet(
            std::string path,
            const json& j_data,
            int tile_width,
            int tile_height
        );
        ~Spritesheet();

        std::unique_ptr<sf::Sprite> get_new_sprite(int frame);
        std::unique_ptr<sf::Sprite> get_new_sprite(sf::IntRect&);

        /* void set_position(double x, double y); */

        const std::unique_ptr<sf::Texture>& get_texture() const;

    private:
        void _insert_tile_info(const json& j_data);
        sf::IntRect _get_rect(int frame);

        std::unique_ptr<sf::Texture> _texture;
        std::string _path;
        int _tile_width;
        int _tile_height;

        int _cols;
        int _rows;
    };
}

#endif
