all:
	g++ -std=c++11 \
		src/main.cpp \
		src/game.cpp \
		src/core/resource_mgr.cpp \
	-lsfml-graphics -lsfml-window -lsfml-system
