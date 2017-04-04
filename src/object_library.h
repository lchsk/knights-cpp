#ifndef OBJECT_LIBRARY_H
#define OBJECT_LIBRARY_H

#include <memory>
#include <unordered_map>

#include "resource_mgr.h"
#include "object_template.h"

namespace ks
{
    class ObjectLibrary
    {
    public:
        ObjectLibrary(std::shared_ptr<ks::ResourceMgr>& resource_mgr);
        ~ObjectLibrary();

        const std::shared_ptr<ks::ObjectTemplate> build_knights_archer();

    private:
        std::unordered_map<std::string, std::shared_ptr<ks::ObjectTemplate> >
            _templates;

        std::shared_ptr<ks::ResourceMgr> _resource_mgr;
    };
}
#endif
