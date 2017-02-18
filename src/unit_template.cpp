#include <iostream>

#include "unit_template.h"

namespace ks
{
    UnitTemplate::UnitTemplate(std::string name, ks::NationType nation)
        : _name(name),
        _nation(nation)
    {
        
    }

    UnitTemplate::~UnitTemplate()
    {
    }

    void UnitTemplate::add_animation(
        std::shared_ptr<ks::ResourceMgr>& resource_mgr,
        const std::string name,
        const std::string image,
        const double speed,
        const std::vector<int>& frames)
    {
        auto anim = std::make_shared<ks::Animation>(
            resource_mgr->get_spritesheet(image),
            frames);

        anim->set_speed(speed);

        _animations[name] = anim;
    }

    UnitLibrary::UnitLibrary(std::shared_ptr<ks::ResourceMgr>& resource_mgr)
        : _resource_mgr(resource_mgr)
    {
        ks::UnitLibrary::KnightsArcher
            = std::make_shared<ks::UnitTemplate>(
                "knights_archer", ks::NationType::Knights);

        ks::UnitLibrary::KnightsArcher->add_animation(
            resource_mgr,
            "stand_up",
            "knights_archer_walk",
            1.0,
            {0});
    }

    UnitLibrary::~UnitLibrary()
    {
    }
}
