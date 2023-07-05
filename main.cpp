#include <iostream>

#include "./src/Game.h"

using namespace std;

int main() {
//    CreateWorld();
    gameT game;
    InitializeGame(game);
    RunSimulation(game);
    return 0;
}
