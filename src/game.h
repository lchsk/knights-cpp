#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "core/resource_mgr.h"
#include "map/level.h"

namespace knights
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
            void update(sf::Time deltaTime);
            void render();

            /* Screen  width */
            int _w;

            /* Screen height */
            int _h;

            std::unique_ptr<knights::map::Level> _current_level;

            std::shared_ptr<knights::res::ResourceMgr> _resource_mgr;

            std::unique_ptr<sf::RenderWindow> _window;
            std::unique_ptr<sf::View> _view;
    };
}
#endif
