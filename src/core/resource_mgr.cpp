#include "resource_mgr.h"

namespace knights
{
    namespace res
    {
        ResourceMgr::ResourceMgr()
        {

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
    }
}
