#include "./main.h"

int main() {
    // Declare vars
    GameData* pGame = NULL;
    UserData  data;
    Callbacks cb;

    // Fill the callback structure
    cb.cbInit   = init;
    cb.cbEvent  = event;
    cb.cbUpdate = update;
    cb.cbDraw   = draw;
    cb.cbFinish = finish;

    // Create the game structure
    pGame = createGame(50,20, &data, &cb, 1);

    // Launch the game
    gameLoop(pGame);

    // end of program
    return 0;
}
