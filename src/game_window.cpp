#include "game_window.h"

namespace knights
{
    GameWindow::GameWindow(
        std::shared_ptr<knights::ResourceMgr> resource_mgr
        )
    {
        _w = 800;
        _h = 600;
        _percent = 5;
        _speed = 200;

        _window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(_w, _h),
            "knights"
            );

        _view = std::make_unique<sf::View>(
            sf::FloatRect(0, 0, _w, _h)
            );

        _window->setView(*_view);
    }

    GameWindow::~GameWindow()
    {

    }

    sf::RenderWindow&
    GameWindow::get_window() const
    {
        return *_window;
    }

    void
    GameWindow::update(sf::Time delta)
    {
        move_view(delta);
        _window->setView(*_view);
    }

    void GameWindow::move_view(sf::Time delta)
    {
        auto mouse_pos = sf::Mouse::getPosition(*_window);

        int move_delta = std::round(_speed * delta.asSeconds());

        if (
            cursor_in(
                CursorPosition::CENTRE,
                move_delta,
                delta,
                mouse_pos
                )) {
            return;
        }

        int dx = 0;
        int dy = 0;

        bool top = cursor_in(
            CursorPosition::TOP,
            move_delta,
            delta,
            mouse_pos
            );

        bool right = cursor_in(
            CursorPosition::RIGHT,
            move_delta,
            delta,
            mouse_pos
            );

        bool left = cursor_in(
            CursorPosition::LEFT,
            move_delta,
            delta,
            mouse_pos
            );

        bool bottom = cursor_in(
            CursorPosition::BOTTOM,
            move_delta,
            delta,
            mouse_pos
            );

        if (bottom)
            dy = move_delta;

        if (top)
            dy = -move_delta;

        if (left)
            dx = -move_delta;

        if (right)
            dx = move_delta;

        if (dx or dy)
            _view->move(dx, dy);
    }

    bool
    GameWindow::cursor_in(
        CursorPosition pos,
        int move_delta,
        sf::Time delta,
        sf::Vector2i mouse_pos
        )
    {
        if (
            pos == CursorPosition::RIGHT
            and mouse_pos.x >= (100 - _percent) / 100.0f * _w
            and _view->getCenter().x + move_delta < _w
            ) {
            return true;
        } else if (
            pos == CursorPosition::LEFT
            and mouse_pos.x < (_percent / 100.0f * _w)
            and _view->getCenter().x - move_delta > _w / 2.0f
            ) {
            return true;
        } else if (
            pos == CursorPosition::BOTTOM
            and mouse_pos.y >= (100 - _percent) / 100.0f * _h
            and  _view->getCenter().y + move_delta < _h
            ) {
            return true;
        } else if (
            pos == CursorPosition::TOP
            and mouse_pos.y < (_percent / 100.0f * _h)
            and _view->getCenter().y - move_delta > _h / 2.0f
            ) {
            return true;
        } else if (
            pos == CursorPosition::CENTRE
            and mouse_pos.x >= (_percent / 100.0f * _w)
            and mouse_pos.x <= (100 - _percent) / 100.0f * _w
            and mouse_pos.y >= (_percent / 100.0f * _h)
            and mouse_pos.y <= (100 - _percent) / 100.0f * _h
            ) {
            return true;
        }

        return false;
    }
}
