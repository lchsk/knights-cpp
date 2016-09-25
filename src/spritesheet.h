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

        /* Texture size in tiles */
        const sf::Vector2u& get_size();

    private:
        void _insert_tile_info(const json& j_data);

        std::unique_ptr<sf::Texture> _texture;
        std::string _path;
        int _tile_width;
        int _tile_height;

        sf::Vector2u _tiles_n;

        std::vector<std::shared_ptr<sf::Sprite> > _sprites;
        std::unordered_map<int, std::shared_ptr<ks::TileInfo> > _tiles_info;
    };
}

#endif
