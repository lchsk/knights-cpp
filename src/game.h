#ifndef GAME_H
#define GAME_H

#include <string>

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

            Game(int x, int y);
            ~Game();

            void run();

        private:
            void handle_events();
            void update(sf::Time deltaTime);
            void render();

            knights::res::ResourceMgr _resource_mgr;

            sf::RenderWindow _window;
            sf::Texture _text;
            sf::Sprite _sp;
    };
}
#endif
