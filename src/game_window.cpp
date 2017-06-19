#include "game_window.h"

namespace ks
{
    GameWindow::GameWindow(const std::shared_ptr<ks::ResourceMgr>& resource_mgr)
        : _map_h(600),
          _map_w(800),
          _w(950),
          _h(600),
          _percent(5),
          _speed(200)
    {
        _window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(_w, _h),
            "knights");

        _view = std::make_unique<sf::View>(sf::FloatRect(0, 0, _w - 2, _h));

        _window->setView(*_view);
    }

    GameWindow::~GameWindow()
    {

    }

    sf::RenderWindow& GameWindow::get_window() const
    {
        return *_window;
    }

    const sf::Vector2f GameWindow::get_top_left() const
    {
        auto c = _view->getCenter();

        c.x -= _w / 2.0;
        c.y -= _h / 2.0;

        return c;
    }

    void GameWindow::update(const sf::Time& delta)
    {
        move_view(delta);
        _window->setView(*_view);
    }

    void GameWindow::move_view(const sf::Time& delta)
    {
        const auto mouse_pos = sf::Mouse::getPosition(*_window);

        const int move_delta = std::round(_speed * delta.asSeconds());

        if (cursor_in(CursorPosition::CENTRE, move_delta, delta, mouse_pos))
            return;

        int dx = 0;
        int dy = 0;

        if (cursor_in(CursorPosition::BOTTOM, move_delta, delta, mouse_pos))
            dy = move_delta;

        if (cursor_in(CursorPosition::TOP, move_delta, delta, mouse_pos))
            dy = -move_delta;

        if (cursor_in(CursorPosition::LEFT, move_delta, delta, mouse_pos))
            dx = -move_delta;

        if (cursor_in(CursorPosition::RIGHT, move_delta, delta, mouse_pos))
            dx = move_delta;

        if (dx or dy)
            _view->move(dx, dy);
    }

    const bool GameWindow::cursor_in(
        const CursorPosition pos,
        const int move_delta,
        const sf::Time& delta,
        const sf::Vector2i& mouse_pos) const
    {
        if (pos == CursorPosition::CENTRE
            and mouse_pos.x >= (_percent / 100.0f * _w)
            and mouse_pos.x <= (100 - _percent) / 100.0f * _w
            and mouse_pos.y >= (_percent / 100.0f * _h)
            and mouse_pos.y <= (100 - _percent) / 100.0f * _h)
            return true;

        if (pos == CursorPosition::RIGHT
            and mouse_pos.x >= (100 - _percent) / 100.0f * _w
            and (_view->getCenter().x + _w / 2.0) < _map_w)
            return true;

        if (pos == CursorPosition::LEFT
            and mouse_pos.x < (_percent / 100.0f * _w)
            and _view->getCenter().x - move_delta > _w / 2.0f - move_delta)
            return true;

        if (pos == CursorPosition::BOTTOM
            and mouse_pos.y >= (100 - _percent) / 100.0f * _h
            and (_view->getCenter().y + _h / 2.0) < _map_h)
            return true;

        if (pos == CursorPosition::TOP
            and mouse_pos.y < (_percent / 100.0f * _h)
            and _view->getCenter().y - move_delta > _h / 2.0f)
            return true;

        return false;
    }

    void GameWindow::set_map_size(const int map_w, const int map_h)
    {
        _map_w = map_w;
        _map_h = map_h;
    }
}
