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
        ObjectTemplate(const std::string name, const ks::NationType nation,
                       const std::vector<int>& block_offset);
        ~ObjectTemplate();

        void add_animation(const std::shared_ptr<ks::Spritesheet>& spritesheet,
                           const std::string name,
                           const double speed,
                           const std::vector<int>& frames);

        void add_animation(const std::shared_ptr<ks::Spritesheet>& spritesheet,
                           const std::string name,
                           const double speed,
                           const std::vector<sf::IntRect>& rects);

        std::shared_ptr<ks::Animation>& get_animation(const std::string);

        const std::vector<int>& get_block_offset() const;

    private:
        const std::string _name;
        const ks::NationType _nation;

        /* _block_offset must have exactly four elements. Each element
           corresponds to the number of graph elements that will separate
           each side. 0th element - top, then clockwise. */
        const std::vector<int> _block_offset;

        std::unordered_map<
            std::string,
            std::shared_ptr<ks::Animation> > _animations;
    };
}
#endif
