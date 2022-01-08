#include "sgpch.h"
#include "Game.h"

int main()
{

    Game *game = new Game();
    while (game->isRunning())
    {
        game->update();
        game->render();
        
    }
    delete game;
    return 0;
}