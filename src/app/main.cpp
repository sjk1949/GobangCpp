#include "app/Application.hpp"
#include "input/ConsoleInput.hpp"

int main() {
    ConsoleUI ui;
    ConsoleInput input;
    Application app(ui, input);
    app.mainLoop();
   
    return 0;
}