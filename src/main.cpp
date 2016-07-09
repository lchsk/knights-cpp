#include <iostream>

#include "game.h"

int main(int argc, char** argv)
{
    knights::Game game(800, 640);
    game.run();

    return 0;
};
