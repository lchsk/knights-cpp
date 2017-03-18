#include <iostream>

#include "unit.h"
#include "util.h"

namespace ks
{
    Unit::Unit(const std::shared_ptr<ks::UnitTemplate>& unit_template)
        : _x(0),
          _y(0),
          _path(std::make_shared<std::vector<ks::Vertex> >()),
          _animation("stand_left"),
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
            set_animation("walk_up");
            break;
        case 2:
            _y += speed * delta.asSeconds();
            set_animation("walk_down");
            break;
        case 1:
            _x += speed * delta.asSeconds();
            set_animation("walk_right");
            break;
        case 3:
            _x -= speed * delta.asSeconds();
            set_animation("walk_left");
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

            switch (dir) {
            case 0:
                set_animation("stand_up");
                break;
            case 2:
                set_animation("stand_down");
                break;
            case 1:
                set_animation("stand_right");
                break;
            case 3:
                set_animation("stand_left");
                break;
            }

            _path->clear();
        }
    }

    void Unit::render(sf::RenderWindow& window)
    {
        #ifdef DEBUG_UNIT_PATHS
        for (auto& step : _debug_path) {
            window.draw(*step);
        }
        #endif

        _unit_template->get_animation(_animation)->render(window);
    }

    const bool Unit::is_walking() const
    {
        return _path->size() > 0;
    }

    void Unit::set_path(
        const std::shared_ptr<std::vector<ks::Vertex> >& path)
    {
        _path->clear();

        #ifdef DEBUG_UNIT_PATHS
        _debug_path.clear();
        #endif

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

        _unit_template->get_animation(_animation)->set_position(x, y);
    }

    const sf::Vector2i Unit::get_position() const
    {
        return sf::Vector2i(_x, _y);
    }

    const sf::Rect<int> Unit::get_rectangle() const
    {
        sf::Rect<int> r(
            _x - ks::UNIT_OFFSET_W,
            _y - ks::UNIT_OFFSET_H,
            ks::UNIT_WIDTH,
            ks::UNIT_HEIGHT);

        return r;
    }

    void Unit::set_animation(const std::string animation)
    {
        _unit_template->get_animation(_animation)->stop();

        _animation = animation;

        set_position(_x, _y);

        _unit_template->get_animation(_animation)->play();
    }
}
