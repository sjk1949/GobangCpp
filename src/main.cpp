#include <iostream>
#include "GameController.h"
#include "ConsoleInput.h"

// ======测试时使用======
#include "..\test\Test.h"
using namespace Test;
// ======测试时使用======

int main() {
    // ======测试用例======
    AITest::testScoreMap();
    // ======测试用例======

    // ======主程序======
    //
    ConsoleUI ui;
    ConsoleInput input;
    GameController gameController(ui, input);
    gameController.runGameLoop(gameController.initGame(gameController.getGameConfig()));
    //
   // ======主程序======
   
    return 0;
}