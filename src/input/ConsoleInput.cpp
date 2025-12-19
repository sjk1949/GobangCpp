#include <iostream>

#include "input/ConsoleInput.hpp"
#include "core/Board.hpp"

/*
InputResult ConsoleInput::getMenuInput() {
    std::string input;
    std::cout << "▷ ";
    std::getline(std::cin, input);
    return parseMenuInput(input);
}
*/

bool ConsoleInput::hasInput() {
    return nbi.kbhit();
}

char ConsoleInput::getInput() {
    return nbi.getch();
}

std::string ConsoleInput::getInput(const std::string& str) {
    std::string input;
    std::cout << str << std::endl;
    std::cout << "▷ ";
    std::getline(std::cin, input);
    return input;
}

