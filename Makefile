all:
	g++ -std=c++11 \
		src/main.cpp \
		src/game.cpp \
		src/core/resource_mgr.cpp \
		src/map/level.cpp \
		src/map/map.cpp \
	-lsfml-graphics -lsfml-window -lsfml-system
