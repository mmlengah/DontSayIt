#include <iostream>
#include "game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv) {
    Game* gameLoop = new Game();
    
    gameLoop->Init();

    while (gameLoop->KeepAlive()) {
        gameLoop->Draw();
        gameLoop->Update();
    }

    gameLoop->Clean();
    delete gameLoop;
    return 0;
}