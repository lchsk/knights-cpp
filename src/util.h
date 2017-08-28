#ifndef UTIL_H
#define UTIL_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace ks
{
	const int UNIT_WIDTH = 64;
	const int UNIT_HEIGHT = 64;

	// TODO: Check if needed
	const int UNIT_OFFSET_W = UNIT_WIDTH / 2;
	const int UNIT_OFFSET_H = UNIT_HEIGHT / 2;

	const int TILE_SIZE = 32;

	// Number of vertices in a row per tile
	const int GRAPH_DEN = 4;

	// Number of pixels between two subsequent vertices in the graph
	constexpr int PX_PER_V = TILE_SIZE / GRAPH_DEN;
	constexpr double PX_PER_VF = static_cast<double>(PX_PER_V);

	inline int flatten_int(int row, int col, int columns) {
		return row * columns + col;
	}

	inline int get_row(int id, int columns) {
		return id / columns;
	}

	inline int get_col(int id, int columns) {
		return id % columns;
	}

#define GET_SPRITEP_WIDTH(sprite) sprite->getLocalBounds().width
#define GET_SPRITEP_HEIGHT(sprite) sprite->getLocalBounds().height

#define GET_SPRITE_WIDTH(sprite) sprite.getLocalBounds().width
#define GET_SPRITE_HEIGHT(sprite) sprite.getLocalBounds().height

	const sf::Color DebugRed = sf::Color(255, 0, 0, 100);
	const sf::Color DebugGreen = sf::Color(0, 255, 0, 100);
}
#endif
