#include <iostream>

#include "game.h"

namespace ks
{
    Game::Game()
    {
        _resource_mgr = std::make_shared<ks::ResourceMgr>();

        _window = std::make_shared<ks::GameWindow>(_resource_mgr);

        _current_level = std::make_unique<ks::Level>(
            _resource_mgr,
            _resource_mgr->get_data_loader(),
            _window
        );
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        sf::Time per_frame = sf::seconds(1.0f / 60.0f);
        sf::Clock clock;
        sf::Time last_update;

        while (_window->get_window().isOpen()) {
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
        _window->update(delta);
        _current_level->update(delta);
    }

    void Game::render()
    {
        _window->get_window().clear();
        _current_level->render(_window->get_window());

        _window->get_window().display();
        _window->render();
    }

    void Game::handle_events()
    {
        sf::Event event;

        while(_window->get_window().pollEvent(event)) {
            const sf::Vector2i pos = sf::Mouse::getPosition(_window->get_window());

			_window->get_hud()->update_events(pos);

            if (event.type == sf::Event::Closed)
                _window->get_window().close();
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (! _window->get_hud()->left_click(pos)) {
                    _current_level->select_objects(pos);
                }
            } else if (
                event.type == sf::Event::KeyPressed
                and event.key.code == sf::Keyboard::Escape
            )
                _window->get_window().close();
        }
    }
}
