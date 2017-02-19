#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "unit_template.h"

namespace ks
{
    class Unit
    {
    public:
        Unit(const std::shared_ptr<ks::UnitTemplate>& unit_template);
        ~Unit();

        void run();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

    private:
        const std::shared_ptr<ks::UnitTemplate>& _unit_template;

        int _x;
        int _y;

        std::string _animation;
    };
}
#endif
