#include "game_window.h"

namespace knights
{
    namespace game
    {
        GameWindow::GameWindow(
            std::shared_ptr<knights::res::ResourceMgr> resource_mgr
            )
        {
        	_w = 800;
        	_h = 600;

        	_window = std::make_unique<sf::RenderWindow>(
            	sf::VideoMode(_w, _h),
            	"knights"
        	);

        	_view = std::make_unique<sf::View>(
            	sf::FloatRect(0, 0, _w, _h)
        	);

        	_window->setView(*_view);
        }

        GameWindow::~GameWindow()
        {

        }

        sf::RenderWindow&
        GameWindow::get_window() const
        {
            return *_window;
        }

        void
        GameWindow::update(sf::Time delta)
        {
        	move_view(delta);
        	_window->setView(*_view);
        }

    void GameWindow::move_view(sf::Time delta)
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

    }
}
