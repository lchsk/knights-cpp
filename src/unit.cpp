#include <iostream>

#include "unit.h"

namespace ks
{
    Unit::Unit(const std::shared_ptr<ks::UnitTemplate>& unit_template)
        : _x(0),
          _y(0),
          _path(std::make_shared<std::vector<ks::Vertex> >()),
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
        if (is_walking()) {
            _move_step(delta);
        }

        _unit_template->get_animation(_animation)->update(delta);
    }

    void Unit::_move_step(sf::Time& delta)
    {
        if (_path->size() < 2) return;

        auto v = (*_path)[0];
        auto next_v = (*_path)[1];

        int dir = get_direction(v.id, next_v.id);

        const int speed = _unit_template->get_speed();

        switch (dir) {
        case 0:
            _y -= speed * delta.asSeconds();
            break;
        case 2:
            _y += speed * delta.asSeconds();
            break;
        case 1:
            _x += speed * delta.asSeconds();
            break;
        case 3:
            _x -= speed * delta.asSeconds();
            break;
        }

        set_position(_x, _y);

        if ((dir == 1 || dir == 3) && fabs(next_v.x - _x) < 0.5) {
            _x = next_v.x;
            _path->erase(_path->begin());
        } else if ((dir == 0 || dir == 2) && fabs(next_v.y - _y) < 0.5) {
            _y = next_v.y;
            _path->erase(_path->begin());
        }

        if (_path->size() == 1) {
            // Path finished
            _path->clear();
        }
    }

    void Unit::render(sf::RenderWindow& window)
    {
        _unit_template->get_animation(_animation)->render(window);

        #ifdef DEBUG_UNIT_PATHS
        for (auto& step : _debug_path) {
            window.draw(*step);
        }
        #endif
    }

    const bool Unit::is_walking() const
    {
        return _path->size() > 0;
    }

    void Unit::set_path(
        const std::shared_ptr<std::vector<ks::Vertex> >& path)
    {
        _path->clear();

        std::vector<ks::Vertex>::reverse_iterator it;

        for (it = path->rbegin(); it != path->rend(); it++) {
            _path->push_back(*it);

            #ifdef DEBUG_UNIT_PATHS
            auto shape = std::make_unique<sf::RectangleShape>();

            shape->setFillColor(sf::Color::Red);
            shape->setSize(sf::Vector2f(8, 8));
            shape->setPosition(sf::Vector2f(it->x, it->y));

            _debug_path.push_back(std::move(shape));
            #endif
        }

        int x = (*_path)[0].x;
        int y = (*_path)[0].y;

        set_position(x , y);
    }

    void Unit::set_position(double x, double y)
    {
        _x = x;
        _y = y;

        _unit_template->get_animation(_animation)->set_position((int)x, (int)y);
    }

    const sf::Vector2i Unit::get_position() const
    {
        return sf::Vector2i(_x, _y);
    }

    void Unit::set_animation(const std::string animation)
    {
        _unit_template->get_animation(_animation)->stop();

        _animation = animation;

        set_position(_x, _y);

        _unit_template->get_animation(_animation)->play();
    }
}
