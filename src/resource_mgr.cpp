
#include "resource_mgr.h"

namespace ks
{
    ResourceMgr::ResourceMgr()
    {
        // std::unique_ptr<knights::Spritesheet> tex =
        //     std::make_unique<
        //     knights::Spritesheet> (
        //     "assets/images/knights_tiles.png",
        //     32,
        //     32
        // );

        _spritesheets["tiles"] = std::make_shared
            <ks::Spritesheet> (
                "assets/images/knights_tiles.png",
                32,
                32
                );

        _spritesheets["knights_archer_walk"] = std::make_shared
            <ks::Spritesheet> (
                "assets/images/knights_archer_walk.png",
                64,
                64
                );
    }

    ResourceMgr::~ResourceMgr()
    {
    }

    void
    ResourceMgr::load_texture(std::string key, std::string path)
    {
        std::unique_ptr<sf::Texture> tex(new sf::Texture());

        if (! tex->loadFromFile(path)) {
            throw std::runtime_error("Unable to load " + path);
        }

        _textures[key] = std::move(tex);
    }

    const sf::Texture&
    ResourceMgr::get_texture(std::string key)
    {
        return *_textures[key];
    }

    ks::Spritesheet&
    ResourceMgr::get_spritesheet(std::string key)
    {
        return *_spritesheets[key];
    }
}
