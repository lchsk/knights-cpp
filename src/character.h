#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "nation.h"
#include "animation.h"
#include "data_loader.h"

namespace ks
{
    class Character
    {
    public:
        Character(
            ks::NationType nation,
            std::string unit_type,
            std::shared_ptr<ks::DataLoader>& data_loader,
            std::shared_ptr<ks::ResourceMgr>& resource_mgr
            );
        ~Character();

        void run();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

    private:
        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Animation>
        > _animations;

        int _x;

        int _y;
    };
}
#endif
