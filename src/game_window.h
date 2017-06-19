#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "resource_mgr.h"
#include "hud.h"

namespace ks
{
    enum class CursorPosition {
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

        GameWindow(const std::shared_ptr<ks::ResourceMgr>& resource_mgr);
        ~GameWindow();

        sf::RenderWindow& get_window() const;
        void update(const sf::Time& delta);
        void render();

        void set_map_size(const int, const int);
        const sf::Vector2f get_top_left() const;

    private:
        void move_view(const sf::Time& delta);

        const bool cursor_in(
            const CursorPosition pos,
            const int move_delta,
            const sf::Time& delta,
            const sf::Vector2i& mouse_pos) const;

        const int _percent;
        int _speed;

        /* Window  width */
        int _w;

        /* Window height */
        int _h;

        /* Map width */
        int _map_w;

        /* Map height */
        int _map_h;

        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<sf::View> _view;
        std::unique_ptr<ks::Hud> _hud;
    };
}

#endif
