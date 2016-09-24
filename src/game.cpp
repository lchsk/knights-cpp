#include <iostream>

#include "game.h"

namespace ks
{
    Game::Game()
    {

        _resource_mgr = std::make_shared<ks::ResourceMgr>();
        _data_loader = std::make_shared<ks::DataLoader>();

        _window = std::make_shared<ks::GameWindow>(
            _resource_mgr
        );

        _current_level = std::make_unique<ks::Level>(
            _resource_mgr,
            _data_loader,
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
    }

    void Game::handle_events()
    {
        sf::Event event;

        while(_window->get_window().pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->get_window().close();
            else if (
                event.type == sf::Event::KeyPressed
                and event.key.code == sf::Keyboard::Escape
            )
                _window->get_window().close();
        }
    }
}
