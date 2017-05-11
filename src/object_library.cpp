#include "object_library.h"

namespace ks
{
    ObjectLibrary::ObjectLibrary(std::shared_ptr<ks::ResourceMgr>& resource_mgr)
        : _resource_mgr(resource_mgr)
    {
    }

    ObjectLibrary::~ObjectLibrary()
    {
    }

    const std::shared_ptr<ObjectTemplate> ObjectLibrary::build_tree()
    {
        const auto tree1 = std::make_shared<ks::ObjectTemplate>
            ("tree1", ks::NationType::Neutral, std::vector<int>({0, 0, 0, 0}));

        const auto& s = _resource_mgr->get_spritesheet_ptr("tiles");

        sf::IntRect r1(270, 590, 100, 150);

        tree1->add_animation(
            s,
            "default",
            1.0,
            {r1});

        return tree1;
    }
}
