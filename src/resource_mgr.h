#ifndef RESOURCE_MGR_H
#define RESOURCE_MGR_H

#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "data_loader.h"
#include "spritesheet.h"

namespace ks
{
    class ResourceMgr
    {
    public:
        ResourceMgr(const ResourceMgr&) = delete;
        ResourceMgr& operator=(const ResourceMgr&) = delete;

        ResourceMgr();
        ~ResourceMgr();

        void load_texture(std::string key, std::string path);

        const sf::Texture&
            get_texture(std::string key);

        /* const std::unique_ptr<sf::Texture>& get_texture_ptr(const std::string key); */

        ks::Spritesheet&
            get_spritesheet(std::string key);

        const std::shared_ptr<ks::Spritesheet>&
            get_spritesheet_ptr(const std::string key);

        std::shared_ptr<ks::DataLoader> get_data_loader();

    private:
        std::unordered_map<
            std::string,
            std::unique_ptr<sf::Texture>
            > _textures;

        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Spritesheet>
            > _spritesheets;

        std::shared_ptr<ks::DataLoader> _data_loader;
    };
}

#endif
