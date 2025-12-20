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
    case 13: // ENTER键
        commandBuffer = std::make_unique<ConfirmCommand>();
        break;
    // 左右调整设置值
    case 'a':
        commandBuffer = std::make_unique<AdjustCommand>(-1);
        break;
    case 'd':
        commandBuffer = std::make_unique<AdjustCommand>(1);
        break;
    }
}