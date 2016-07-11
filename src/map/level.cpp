#include "level.h"

namespace knights
{
    namespace map
    {
        Level::Level(std::shared_ptr<knights::res::ResourceMgr>& resource_mgr)
            : _resource_mgr(resource_mgr)
        {
        }

        Level::~Level()
        {

        }
    }
}
