#include <iostream>

#include "object_template.h"

namespace ks
{
    ObjectTemplate::ObjectTemplate(const std::string name,
                                   const ks::NationType nation,
                                   const std::vector<int>& block_offset)
        : _name(name),
          _nation(nation),
          _block_offset(block_offset)
    {
        assert(_block_offset.size() == 4);
    }

    ObjectTemplate::~ObjectTemplate()
    {
    }

    void ObjectTemplate::add_animation(const std::shared_ptr<ks::Spritesheet>&
                                       spritesheet,
                                       const std::string name,
                                       const double speed,
                                       const std::vector<int>& frames)
    {
        auto anim = std::make_shared<ks::Animation>(spritesheet, frames);

        anim->set_speed(speed);

        _animations[name] = anim;
    }

    void ObjectTemplate::add_animation(const std::shared_ptr<ks::Spritesheet>&
                                       spritesheet,
                                       const std::string name,
                                       const double speed,
                                       const std::vector<sf::IntRect>& rects)
    {
        auto anim = std::make_shared<ks::Animation>(spritesheet, rects);

        anim->set_speed(speed);

        _animations[name] = anim;
    }

    std::shared_ptr<ks::Animation>&
    ObjectTemplate::get_animation(const std::string name)
    {
        return _animations[name];
    }

    const std::vector<int>& ObjectTemplate::get_block_offset() const
    {
        return _block_offset;
    }
}
