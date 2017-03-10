#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <memory>
#include <unordered_map>

#include "../thirdparty/json/src/json.hpp"

#include <SFML/Graphics.hpp>

using json = nlohmann::json;

namespace ks
{
    class TileInfo
    {
    public:
        TileInfo(int id);
        ~TileInfo();

    private:
        int _id;
    };

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

        std::shared_ptr<sf::Sprite>& get(int row, int col);
        std::shared_ptr<sf::Sprite>& get(int frame);

        std::unique_ptr<sf::Sprite> get_new_sprite(int frame);

        void set_position(double x, double y);

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

        // TODO: Can this Sprite a unique_ptr?
        std::vector<std::shared_ptr<sf::Sprite> > _sprites;
        std::unordered_map<int, std::shared_ptr<ks::TileInfo> > _tiles_info;
    };
}

#endif
