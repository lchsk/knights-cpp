#ifndef RESOURCE_MGR_H
#define RESOURCE_MGR_H

#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "spritesheet.h"

namespace knights
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

        knights::Spritesheet&
            get_spritesheet(std::string key);

    private:
        std::unordered_map<
            std::string,
            std::unique_ptr<sf::Texture>
            > _textures;

        std::unordered_map<
            std::string,
            std::shared_ptr<knights::Spritesheet>
            > _spritesheets;

    };
}

#endif
