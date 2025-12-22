#include <iostream>
#include "app/Application.hpp"
#include "input/ConsoleInput.hpp"

// ======测试时使用======
#include "test\Test.hpp"
using namespace Test;
// ======测试时使用======

int main() {
    // ======测试用例======
    //JudgeTest::testChessPattern();
    // ======测试用例======

    // ======主程序======
    //
    ConsoleUI ui;
    ConsoleInput input;
    Application app(ui, input);
    app.mainLoop();
    //app.runGameLoop(app.initGame(app.getGameConfig()));
    //
   // ======主程序======
   
    return 0;
}