#include <iostream>

#include "object.h"
#include "util.h"

namespace ks
{
    Object::Object(const std::shared_ptr<ks::ObjectTemplate>& unit_template)
        : _x(0),
          _y(0),
          _path(std::make_shared<std::vector<ks::Vertex> >()),
          _animation("default"),
          _unit_template(unit_template)
    {
        _unit_template->get_animation(_animation)->play();
    }

    Object::~Object()
    {
    }

    void Object::update(sf::Time delta)
    {
        _unit_template->get_animation(_animation)->update(delta);
    }

    void Object::render(sf::RenderWindow& window)
    {
        #ifdef DEBUG_UNIT_PATHS
        for (auto& step : _debug_path) {
            window.draw(*step);
        }
        #endif

        _unit_template->get_animation(_animation)->render(window);
    }

    const std::shared_ptr<std::vector<ks::Vertex> > Object::get_path() const
    {
        return _path;
    }

    const std::shared_ptr<ks::ObjectTemplate> Object::get_template() const
    {
        return _unit_template;
    }

    const bool Object::is_walking() const
    {
        return _path->size() > 0;
    }

    const ks::MapObjectType Object::get_type() const
    {
        return ks::MapObjectType::Other;
    }

    void Object::set_path(
        const std::shared_ptr<std::vector<ks::Vertex> >& path)
    {
        assert(path->size());

        if (is_walking()) {
            _path->erase(_path->begin() + 1, _path->end());
        }

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

        if (! is_walking()) {
            double x = (*_path)[0].x;
            double y = (*_path)[0].y;

            set_position(x , y);
        }
    }

    void Object::set_position(double x, double y)
    {
        _x = x;
        _y = y;

        _unit_template->get_animation(_animation)->set_position(x, y);
    }

    const sf::Vector2f Object::get_position() const
    {
        return sf::Vector2f(_x, _y);
    }

    const sf::Rect<int> Object::get_rectangle() const
    {
        sf::Rect<int> r(
            _x - ks::UNIT_OFFSET_W,
            _y - ks::UNIT_OFFSET_H,
            ks::UNIT_WIDTH,
            ks::UNIT_HEIGHT);

        return r;
    }

    const ks::Vertex& Object::get_current_target() const
    {
        assert(_path->size() >= 2);

        return (*_path)[1];
    }

    void Object::pop_path_step() const
    {
        _path->erase(_path->begin());
    }

    void Object::clear_path() const
    {
        _path->clear();
    }

    void Object::set_animation(const std::string animation)
    {
        _unit_template->get_animation(_animation)->stop();

        _animation = animation;

        set_position(_x, _y);

        _unit_template->get_animation(_animation)->play();
    }
}
