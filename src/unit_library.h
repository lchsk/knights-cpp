#ifndef UNIT_LIBRARY_H
#define UNIT_LIBRARY_H

#include <memory>
#include <unordered_map>

#include "resource_mgr.h"
#include "unit_template.h"

namespace ks
{
    class UnitLibrary
    {
    public:
        UnitLibrary(std::shared_ptr<ks::ResourceMgr>& resource_mgr);
        ~UnitLibrary();

        const std::shared_ptr<ks::UnitTemplate> build_knights_archer();

    private:
        std::unordered_map<std::string, std::shared_ptr<ks::UnitTemplate> >
            _templates;

        std::shared_ptr<ks::ResourceMgr> _resource_mgr;
    };
}
#endif
