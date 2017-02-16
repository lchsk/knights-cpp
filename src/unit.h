#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "nation.h"
#include "animation.h"
#include "data_loader.h"
#include "resource_mgr.h"

namespace ks
{

    class Unit
    {
    public:
        Unit(
            ks::NationType nation,
            std::string unit_type,
            std::shared_ptr<ks::DataLoader>& data_loader,
            std::shared_ptr<ks::ResourceMgr>& resource_mgr
            );
        ~Unit();

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

        ks::NationType _nation;
        std::string _unit_name;

        std::string _animation;
    };
}
#endif
