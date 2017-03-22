#ifndef UTIL_H
#define UTIL_H

namespace ks
{
	const int UNIT_WIDTH = 64;
	const int UNIT_HEIGHT = 64;
	const int UNIT_OFFSET_W = UNIT_WIDTH / 2;
	const int UNIT_OFFSET_H = UNIT_HEIGHT / 2;

	const int TILE_SIZE = 32;

	// Number of vertices in a row per tile
	const int GRAPH_DEN = 4;

	// Numbrer of pixels between two subsequent vertices in the graph
	const int PX_PER_V = TILE_SIZE / GRAPH_DEN;

	inline int flatten_int(int row, int col, int columns) {
		return row * columns + col;
	}

	inline int get_row(int id, int columns) {
		return id / columns;
	}

	inline int get_col(int id, int columns) {
		return id % columns;
	}
}
#endif
