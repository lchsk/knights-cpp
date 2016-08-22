#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "nation.h"

namespace knights
{
    class Character
    {
    public:
        Character(knights::Nation nation);
        ~Character();

        void run();

    private:
        void update(sf::Time delta);
        void render();
    };
}
#endif
