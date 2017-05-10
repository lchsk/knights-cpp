#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "object_template.h"
#include "graph.h"
#include "map_object.h"

#define DEBUG_UNIT_PATHS

namespace ks
{
    class Object : public ks::MapObject
    {
    public:
        // TODO: unique?
        Object(const std::shared_ptr<ks::ObjectTemplate>& unit_template);
        ~Object();

        void run();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        void set_position(const double x, const double y);
        const sf::Vector2f get_position() const;
        void set_animation(const std::string animation);

        void set_path(const std::shared_ptr<std::vector<ks::Vertex> >& path);

        void pop_path_step() const;
        void clear_path() const;
        const ks::Vertex& get_current_target() const;

        const sf::Rect<int> get_rectangle() const;
        const std::shared_ptr<std::vector<ks::Vertex> > get_path() const;
        const std::shared_ptr<ks::ObjectTemplate> get_template() const;

        const bool is_walking() const;

        virtual const MapObjectType get_type() const;
    private:
        const std::shared_ptr<ks::ObjectTemplate> _unit_template;

        double _x;
        double _y;

        std::string _animation;

        std::shared_ptr<std::vector<ks::Vertex> > _path;

        #ifdef DEBUG_UNIT_PATHS
        std::vector<std::unique_ptr<sf::RectangleShape> > _debug_path;
        #endif
    };
}
#endif
