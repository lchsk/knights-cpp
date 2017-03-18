#include <iostream>

#include "unit_template.h"

namespace ks
{
    UnitTemplate::UnitTemplate(std::string name, ks::NationType nation,
                               const int speed)
        : _name(name),
          _nation(nation),
          _speed(speed)
    {
        
    }

    UnitTemplate::~UnitTemplate()
    {
    }

    void UnitTemplate::add_animation(
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
    UnitTemplate::get_animation(const std::string name)
    {
        return _animations[name];
    }

    const int UnitTemplate::get_speed() const
    {
        return _speed;
    }
}
