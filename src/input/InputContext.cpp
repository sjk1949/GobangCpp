#include "input/InputContext.h"

#include "command/Command.h"

InputContext::InputContext() {}

std::unique_ptr<Command> InputContext::popCommand() {
    std::unique_ptr<Command> command = std::move(commandBuffer);
    commandBuffer = nullptr;
    return command;
}