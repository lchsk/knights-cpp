#include <iostream>

#include "game.h"

namespace knights
{
    Game::Game(int x, int y)
        : _window(sf::VideoMode(x, y), "knights")
    {
        _resource_mgr.load_texture(
            "archer",
            "assets/images/knights_archer_bow.png"
        );
        _sp.setTexture(_resource_mgr.get_texture("archer"));
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        sf::Clock clock;
        sf::Time since_last_update;
        sf::Time per_frame = sf::seconds(1.0f / 60.0f);

        while (_window.isOpen()) {
            bool repaint = false;

            sf::Time delta = clock.restart();
            since_last_update += delta;

            if (since_last_update > per_frame) {
                handle_events();

                since_last_update -= per_frame;
                repaint = true;

                update(since_last_update);
            }

            if (repaint)
                render();
        }
    }

    void Game::update(sf::Time delta)
    {
    }

    void Game::render()
    {
        _window.clear();
        _window.draw(_sp);

        _window.display();
    }

    void Game::handle_events()
    {
        sf::Event event;

        while(_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
                _window.close();
        }
    }
}
