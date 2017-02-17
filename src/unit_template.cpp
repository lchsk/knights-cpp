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

    namespace units
    {
        void init_units()
        {
        }
    }
}
