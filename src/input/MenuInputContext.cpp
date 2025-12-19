#include "input/MenuInputContext.hpp"

#include "command/MenuCommand.hpp"
#include "utils/Logger.hpp"

void MenuInputContext::onInput(const char& c) {
    Logger::debug("PRESSED: ", int(c), " ", c);
    switch (c)
    {
    case 'w':
        commandBuffer = std::make_unique<MoveUpCommand>();
        break;
    case 's':
        commandBuffer = std::make_unique<MoveDownCommand>();
        break;
    case 13:
        commandBuffer = std::make_unique<ConfirmCommand>();
        break;
    }
}