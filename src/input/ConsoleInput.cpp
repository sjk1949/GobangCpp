#include <iostream>

#include "input/ConsoleInput.hpp"
#include "core/Board.hpp"

bool ConsoleInput::hasInput() {
    return nbi.kbhit();
}

char ConsoleInput::getInput() {
    return nbi.getch();
}