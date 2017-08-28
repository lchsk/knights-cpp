#ifndef COMMON_H
#define COMMON_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "util.h"

namespace ks
{
	struct Size {
		int width;
		int height;

		void read(const sf::Sprite& sprite) {
		    width = GET_SPRITE_WIDTH(sprite);
			height = GET_SPRITE_HEIGHT(sprite);
		}
	};
}
#endif
