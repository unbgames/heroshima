#include <state/TitleState.h>
#include "engine/Game.h"

int main (int argc, char** argv) {
    auto &game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();

    return 0;
}