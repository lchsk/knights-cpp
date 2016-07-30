#ifndef NATION_H
#define NATION_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace knights
{
    namespace data
    {
        class nation_t
        {
        public:
            nation_t(const nation_t&) = delete;
            nation_t& operator=(const nation_t&) = delete;
        };
    }
}
#endif
