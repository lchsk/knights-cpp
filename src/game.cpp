#include <iostream>
#include <cmath>

#include "game.h"

namespace knights
{
    Game::Game()
    {
        _w = 800;
        _h = 600;

        _resource_mgr = std::make_shared<knights::res::ResourceMgr>();

        _current_level = std::make_unique<knights::map::Level>(
            _resource_mgr
        );

        _window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(_w, _h),
            "knights"
        );

        _view = std::make_unique<sf::View>(
            sf::FloatRect(0, 0, _w, _h)
        );

        _window->setView(*_view);

        // _view->move(1200, 200);
    }

    Game::~Game()
    {
    }

    void Game::move_view(sf::Time delta)
    {
        auto v = sf::Mouse::getPosition(*_window);

        int percent = 5;
        int speed = 200;

        int val = std::round(speed * delta.asSeconds());

        if (v.x >= (100 - percent) / 100.0f * _w
            && _view->getCenter().x + val < _w
        ) {
            _view->move(val, 0);
        }
        else if (v.x < (percent / 100.0f * _w)
              && _view->getCenter().x - val > _w / 2.0f
            ) {
            _view->move(-val, 0);
        }
        else if (v.y >= (100 - percent) / 100.0f * _h
            && _view->getCenter().y + val < _h
        ) {
            _view->move(0, val);
        }
        else if (v.y < (percent / 100.0f * _h)
              && _view->getCenter().y - val > _h / 2.0f
            ) {
            _view->move(0, -val);
        }
    }

    void Game::run()
    {
        sf::Time per_frame = sf::seconds(1.0f / 60.0f);
        sf::Clock clock;
        sf::Time last_update;

        while (_window->isOpen()) {
            sf::Time diff = clock.getElapsedTime() - last_update;

            if (diff > per_frame) {
                handle_events();
                update(diff);
                render();
                last_update = clock.getElapsedTime();
            }
        }
    }

    void Game::update(sf::Time delta)
    {
        move_view(delta);
        _window->setView(*_view);
        _current_level->update(delta);
    }

    void Game::render()
    {
        _window->clear();
        _current_level->render(*_window);

        _window->display();
    }

    void Game::handle_events()
    {
        sf::Event event;

        while(_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
                _window->close();
        }
    }
}
