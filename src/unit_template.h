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
        std::string test;
    private:
        std::string _name;
        ks::NationType _nation;

        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Animation>
        > _animations;
    };

    namespace units
    {
        void init_units();
    }
}
#endif
