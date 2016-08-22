#ifndef NATION_H
#define NATION_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace knights
{
    enum NationType {
        Knights,
        Skeletons
    };

    class Nation
    {
    public:
        Nation();
        ~Nation();
    };
}
#endif
