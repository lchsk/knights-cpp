#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace knights
{
    namespace game
    {
        class Character
        {
        public:
            Character(const Character&) = delete;
            Character& operator=(const Character&) = delete;

            Character();
            ~Character();

            void run();

        private:
            void update(sf::Time delta);
            void render();
        };
    }
}
#endif
