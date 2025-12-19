#include "input/InputContext.hpp"

#include "command/Command.hpp"

InputContext::InputContext() {}

std::unique_ptr<Command> InputContext::popCommand() {
    std::unique_ptr<Command> command = std::move(commandBuffer);
    commandBuffer = nullptr;
    return command;
}