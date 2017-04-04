#include <iostream>

#include "object_template.h"

namespace ks
{
    ObjectTemplate::ObjectTemplate(std::string name, ks::NationType nation)
        : _name(name),
          _nation(nation)
    {
    }

    ObjectTemplate::~ObjectTemplate()
    {
    }

    void ObjectTemplate::add_animation(
        const std::shared_ptr<ks::Spritesheet>& spritesheet,
        const std::string name,
        const double speed,
        const std::vector<int>& frames)
    {
        auto anim = std::make_shared<ks::Animation>(spritesheet, frames);

        anim->set_speed(speed);

        _animations[name] = anim;
    }

    std::shared_ptr<ks::Animation>&
    ObjectTemplate::get_animation(const std::string name)
    {
        return _animations[name];
    }
}
