#ifndef UTIL_H
#define UTIL_H

namespace ks
{
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
