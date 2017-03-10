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

    UnitLibrary::UnitLibrary(std::shared_ptr<ks::ResourceMgr>& resource_mgr)
        : _resource_mgr(resource_mgr)
    {
    }

    UnitLibrary::~UnitLibrary()
    {
    }

    const std::shared_ptr<UnitTemplate> UnitLibrary::build_knights_archer()
    {
        const auto unit = std::make_shared<ks::UnitTemplate>(
            "knights_archer", ks::NationType::Knights);

        const auto& s = _resource_mgr->get_spritesheet_ptr(
            "knights_archer_walk");

        unit->add_animation(
            s,
            "stand_up",
            1.0,
            {0});
        unit->add_animation(
            s,
            "stand_left",
            1.0,
            {9});
        unit->add_animation(
            s,
            "stand_down",
            1.0,
            {18});
        unit->add_animation(
            s,
            "stand_right",
            1.0,
            {27});

        unit->add_animation(
            s,
            "walk_up",
            0.5,
            {1, 2, 3, 4, 5, 6, 7, 8});
        unit->add_animation(
            s,
            "walk_left",
            0.5,
            {10, 11, 12, 13, 14, 15, 16, 17});
        unit->add_animation(
            s,
            "walk_down",
            0.5,
            {19, 20, 21, 22, 23, 24, 25, 26});
        unit->add_animation(
            s,
            "walk_right",
            0.5,
            {28, 29, 30, 31, 32, 33, 34, 35});

        return unit;
    }
}
