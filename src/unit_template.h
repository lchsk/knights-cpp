#ifndef UNIT_TEMPLATE_H
#define UNIT_TEMPLATE_H

#include <string>
#include <memory>
#include <unordered_map>

#include "nation.h"
#include "animation.h"
#include "resource_mgr.h"

namespace ks
{
    class UnitTemplate
    {
    public:
        UnitTemplate(std::string name, ks::NationType nation, const int speed);
        ~UnitTemplate();

        void add_animation(
            const std::shared_ptr<ks::Spritesheet>& spritesheet,
            const std::string name,
            const double speed,
            const std::vector<int>& frames);

        std::shared_ptr<ks::Animation>& get_animation(const std::string);
        const int get_speed() const;

    private:
        std::string _name;
        ks::NationType _nation;
        const int _speed;

        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Animation> > _animations;
    };
}
#endif
