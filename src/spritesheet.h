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
        enum class SpritesheetType {
            Grid,
            Named
        };

    public:
        /* For grid-like spritesheets: every item next to each other */
        Spritesheet(std::string path,
                    /* const json& j_data, */
                    int tile_width,
                    int tile_height);

        /* For named spritesheets that have images scattered around; requires */
        /* a json that describes the spritesheet. */
        Spritesheet(std::string path,
                    const json& desc);

        ~Spritesheet();

        std::unique_ptr<sf::Sprite> get_new_sprite(int frame);
        std::unique_ptr<sf::Sprite> get_new_sprite(sf::IntRect&);
        std::unique_ptr<sf::Sprite> get_new_sprite_by_key(const std::string&);

        const std::unique_ptr<sf::Texture>& get_texture() const;

    private:
        void _load_desc(const json& data);
        sf::IntRect _get_rect(int frame);

        std::unordered_map<std::string, sf::IntRect> _desc;
        std::unordered_map<int, sf::IntRect> _desc_frames;

        const SpritesheetType _type;
        std::unique_ptr<sf::Texture> _texture;
        std::string _path;
        int _tile_width;
        int _tile_height;

        int _cols;
        int _rows;
    };
}

#endif
