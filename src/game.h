#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "resource_mgr.h"
#include "game_window.h"
#include "level.h"

namespace ks
{
    class Game
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game();
            ~Game();

            void run();

        private:
            void handle_events();
            void update(sf::Time delta);
            void render();

            std::unique_ptr<ks::Level> _current_level;
            std::shared_ptr<ks::GameWindow> _window;

            std::shared_ptr<ks::ResourceMgr> _resource_mgr;
    };
}
#endif
