#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <memory>

namespace ks
{
    enum class MapObjectType {
        Unit,
        Other
    };

    class MapObject
    {
    public:
        MapObject() {};
        ~MapObject() {};

        virtual void update(sf::Time delta) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        virtual void set_position(const double x, const double y) = 0;
        virtual const sf::Vector2f get_position() const = 0;

        virtual const bool is_walking() const = 0;
        virtual const sf::Rect<int> get_rectangle() const = 0;

        virtual const MapObjectType get_type() const = 0;
    };

    inline const bool map_object_y_pos_sorter(const std::shared_ptr
                                              <ks::MapObject>& mo1,
                                              const std::shared_ptr
                                              <ks::MapObject>& mo2) {
        return mo1->get_position().y < mo2->get_position().y;
    }
}
#endif
