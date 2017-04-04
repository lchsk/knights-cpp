#ifndef OBJECT_TEMPLATE_H
#define OBJECT_TEMPLATE_H

#include <string>
#include <memory>
#include <unordered_map>

#include "nation.h"
#include "animation.h"
#include "resource_mgr.h"

namespace ks
{
    class ObjectTemplate
    {
    public:
        ObjectTemplate(std::string name, ks::NationType nation);
        ~ObjectTemplate();

        void add_animation(
            const std::shared_ptr<ks::Spritesheet>& spritesheet,
            const std::string name,
            const double speed,
            const std::vector<int>& frames);

        std::shared_ptr<ks::Animation>& get_animation(const std::string);

    private:
        std::string _name;
        ks::NationType _nation;

        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Animation> > _animations;
    };
}
#endif
