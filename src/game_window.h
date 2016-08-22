#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "resource_mgr.h"

namespace ks
{
    enum CursorPosition {
        TOP,
        LEFT,
        RIGHT,
        BOTTOM,
        // Cursor is placed far enough from the borders so the view
        // will not be moved.
        CENTRE
    };

    class GameWindow
    {
    public:
        GameWindow(const GameWindow&) = delete;
        GameWindow& operator=(const GameWindow&) = delete;

        GameWindow(
            std::shared_ptr<ks::ResourceMgr> resource_mgr
            );
        ~GameWindow();

        sf::RenderWindow& get_window() const;
        void update(sf::Time delta);

    private:
        void move_view(sf::Time delta);

        bool cursor_in(
            CursorPosition pos,
            int move_delta,
            sf::Time delta,
            sf::Vector2i mouse_pos
            );

        int _percent;
        int _speed;

        /* Screen  width */
        int _w;

        /* Screen height */
        int _h;

        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<sf::View> _view;
    };
}

#endif
