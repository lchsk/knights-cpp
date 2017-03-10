#include <iostream>

#include "unit.h"

namespace ks
{
    Unit::Unit(const std::shared_ptr<ks::UnitTemplate>& unit_template)
        : _x(0),
          _y(0),
          _animation("walk_left"),
          _unit_template(unit_template)
    {
        _unit_template->get_animation(_animation)->play();
    }

    Unit::~Unit()
    {
    }

    void Unit::update(sf::Time delta)
    {
        _unit_template->get_animation(_animation)->update(delta);
    }

    void Unit::render(sf::RenderWindow& window)
    {
        _unit_template->get_animation(_animation)->render(window);
    }

    void Unit::set_position(double x, double y)
    {
        _x = x;
        _y = y;

        _unit_template->get_animation(_animation)->set_position(x, y);
    }

    void Unit::set_animation(const std::string animation)
    {
        _unit_template->get_animation(_animation)->stop();

        _animation = animation;

        set_position(_x, _y);

        _unit_template->get_animation(_animation)->play();
    }
}
