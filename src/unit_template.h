#ifndef UNIT_DEFINITION_H
#define UNIT_DEFINITION_H

#include <string>
#include <memory>
#include <unordered_map>

#include "nation.h"
#include "animation.h"
#include "data_loader.h"
#include "resource_mgr.h"

namespace ks
{
    class UnitTemplate
    {
    public:
        UnitTemplate(std::string name, ks::NationType nation);
        ~UnitTemplate();

        void add_animation(
            std::shared_ptr<ks::ResourceMgr>& resource_mgr,
            const std::string name,
            const std::string image,
            const double speed,
            const std::vector<int>& frames);

    private:
        std::string _name;
        ks::NationType _nation;

        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Animation> > _animations;
    };

    class UnitLibrary
    {
    public:
        UnitLibrary(std::shared_ptr<ks::ResourceMgr>& resource_mgr);
        ~UnitLibrary();

    private:
        std::shared_ptr<UnitTemplate> KnightsArcher;

        std::shared_ptr<ks::ResourceMgr> _resource_mgr;
    };
}
#endif
