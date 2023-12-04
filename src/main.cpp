#include <iostream>
#include "./headers/Game.h"
#include <SFML/Graphics.hpp>

int main()
{
    Game game;
    
    while (game.isWindowOpen)
        game.run();
}