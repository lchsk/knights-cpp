#include <iostream>

#include "character.h"
#include "data_loader.h"

namespace ks
{
    Character::Character(
        ks::NationType nation,
        std::string unit_name,
        std::shared_ptr<ks::DataLoader>& data_loader,
        std::shared_ptr<ks::ResourceMgr>& resource_mgr
    ) :
        _x(0),
        _y(0),
        _animation("stand_left"),
        _nation(nation),
        _unit_name(unit_name)
    {
        auto animations = data_loader->get_json(unit_name)["animations"];

        json::iterator it = animations.begin();

        for (; it != animations.end(); ++it) {
            std::vector<int> frames = it.value()["frames"];

            auto a = std::make_shared<ks::Animation>(
                resource_mgr->get_spritesheet(it.value()["image"]),
                frames
                );

            a->set_speed(it.value()["speed"]);
            a->play();

            std::string name = it.key();

            _animations[name] = a;
        }
    }

    Character::~Character()
    {
    }

    void Character::update(sf::Time delta)
    {
        _animations[_animation]->update(delta);
    }

    void Character::render(sf::RenderWindow& window)
    {
        _animations[_animation]->render(window);

    }
}
