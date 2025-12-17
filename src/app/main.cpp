#include <iostream>
#include "app/Application.h"
#include "input/ConsoleInput.h"

// ======测试时使用======
#include "..\test\Test.h"
using namespace Test;
// ======测试时使用======

int main() {
    // ======测试用例======
    //InputTest::testNonBlockingInput();
    // ======测试用例======

    // ======主程序======
    //
    ConsoleUI ui;
    ConsoleInput input;
    Application app(ui, input);
    app.runGameLoop(app.initGame(app.getGameConfig()));
    //
   // ======主程序======
   
    return 0;
}