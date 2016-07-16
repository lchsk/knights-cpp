#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "resource_mgr.h"

namespace knights
{
    namespace game
    {
        class GameWindow
        {
            public:
                GameWindow(const GameWindow&) = delete;
                GameWindow& operator=(const GameWindow&) = delete;

                GameWindow(
                    std::shared_ptr<knights::res::ResourceMgr> resource_mgr
                );
                ~GameWindow();

                sf::RenderWindow& get_window() const;
                void update(sf::Time delta);

            private:
                            void move_view(sf::Time delta);
	                       /* Screen  width */
            int _w;

            /* Screen height */
            int _h;
            std::unique_ptr<sf::RenderWindow> _window;
            std::unique_ptr<sf::View> _view;
        };
    }
}

#endif
