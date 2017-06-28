#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace ks
{
    enum class ButtonState {
        Ready,
        Hover
    };

    class Button
    {
    public:
        Button();
        ~Button();

        const ButtonState getState() const;

        void run();

        void update(sf::Time delta);
        void render(sf::RenderWindow& window);

        void add_state(ButtonState, std::unique_ptr<sf::Sprite>&&);
        void update_events(const sf::Vector2i&);

    private:
        sf::Vector2i _pos;

        ButtonState _state;

        std::unordered_map<ButtonState, std::unique_ptr<sf::Sprite> >
            _state_sprites;
    };
}
#endif
