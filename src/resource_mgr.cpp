
#include "resource_mgr.h"
#include "util.h"

namespace ks
{
    ResourceMgr::ResourceMgr()
    {
        _data_loader = std::make_shared<ks::DataLoader>();

        _spritesheets["tiles"] = std::make_shared
            <ks::Spritesheet>("assets/images/knights_tiles.png",
                              _data_loader->get_json("knights_tiles"), 32, 32);

        _spritesheets["knights_archer_walk"] = std::make_shared
            <ks::Spritesheet>("assets/images/knights_archer_walk.png",
                              nullptr, ks::UNIT_WIDTH, ks::UNIT_HEIGHT);
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

    // const std::unique_ptr<sf::Texture>&
    // ResourceMgr::get_texture_ptr(const std::string key)
    // {
        // return _textures[key];
    // }

    ks::Spritesheet&
    ResourceMgr::get_spritesheet(std::string key)
    {
        return *_spritesheets[key];
    }

    const std::shared_ptr<ks::Spritesheet>&
    ResourceMgr::get_spritesheet_ptr(const std::string key)
    {
        return _spritesheets[key];
    }


    std::shared_ptr<ks::DataLoader> ResourceMgr::get_data_loader()
    {
        return _data_loader;
    }
}
