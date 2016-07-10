#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "core/resource_mgr.h"

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

            knights::res::ResourceMgr _resource_mgr;

            std::unique_ptr<sf::RenderWindow> _window;
            sf::Texture _text;
            sf::Sprite _sp;
    };
}
#endif
