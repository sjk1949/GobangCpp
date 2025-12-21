#include "app/Application.hpp"

#include <chrono>
#include <thread>
#include "core/Game.hpp"
#include "menu/MenuSet.hpp"
#include "player/HumanPlayer.hpp"
#include "player/AIPlayer.hpp"
#include "command/MenuCommand.hpp"
#include "input/GameInputContext.hpp"
#include "input/MenuInputContext.hpp"
#include "utils/Logger.hpp"

Application::Application(ConsoleUI& ui, InputDevice& input) : ui(ui), input(input) {
    state = AppState::MAIN_MENU;
    menu = MenuSet::createMainMenu();
    menu.setApp(*this);
    gameConfig = createDefaultConfig();
    initTime = std::chrono::steady_clock::now();
    inputContext = std::make_unique<MenuInputContext>();
}

GameConfig& Application::getGameConfig() {
    return gameConfig;
}

const GameConfig& Application::getGameConfig() const {
    return gameConfig;
}

void Application::mainLoop() {
    while (state != AppState::EXIT) {
        std::chrono::milliseconds startTime = getCurrentTime();
        processInput();
        update();
        render();

        sleep(startTime + MS_PER_FRAME - getCurrentTime());
    }
}

GameConfig Application::createDefaultConfig() {
    return GameConfig();
}

void Application::changeState(AppState state) {
    if (state == AppState::MAIN_MENU) {
        inputContext = std::make_unique<MenuInputContext>();
    } else if (state == AppState::GAME_RUNNING) {
        inputContext = std::make_unique<GameInputContext>();
    }
    this->state = state;
}

void Application::processInput() {
    if (state == AppState::MAIN_MENU) {
        if (input.hasInput()) {
            char c = input.getInput();
            inputContext->onInput(c);
            std::unique_ptr<Command> command = inputContext->popCommand();
            if (!command) return;
            if (auto* menuCommand = dynamic_cast<MenuCommand*>(command.get()))
            {
                command.release(); // 释放基类指针的所有权
                std::unique_ptr<MenuCommand> mc(menuCommand); // 用派生类型重新接管
                menu.handleInput(std::move(mc));
            }
        }
    } else if (state == AppState::GAME_RUNNING) {
        if (input.hasInput()) {
            char c = input.getInput();
            inputContext->onInput(c);
            std::unique_ptr<Command> command = inputContext->popCommand();
            if (!command) return;
            if (auto* gameCommand = dynamic_cast<GameCommand*>(command.get()))
            {
                command.release(); // 释放基类指针的所有权
                std::unique_ptr<GameCommand> gc(gameCommand); // 用派生类型重新接管
                game->handleInput(std::move(gc));
            }
        }
    }
}

void Application::update() {
    frame++;
    //Logger::info("Frame: ", frame);
    if (state == AppState::GAME_RUNNING) {
        game->update();
        if (game->getGameState() == GameState::QUIT) {
            changeState(AppState::MAIN_MENU);
        }
    }
}

void Application::render() {
    ui.clear();
    if (state == AppState::MAIN_MENU) {
        ui.displayMenu(menu);
    } else if (state == AppState::GAME_RUNNING) {
        ui.displayGame(*game);
        ui.print(inputContext->getBuffer(), "\n");
    } else if (state == AppState::EXIT) { // 应用退出的时候不再刷新屏幕
        return;
    }
    ui.print("Frame: ", frame, "\n");
    ui.drawDebugPanel();
    ui.flip();
}

void Application::startGame() {
    game = std::make_unique<Game>(getGameConfig());
    changeState(AppState::GAME_RUNNING);
}

void Application::exit() {
    changeState(AppState::EXIT);
}

std::chrono::milliseconds Application::getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - initTime);
}

void Application::sleep(std::chrono::milliseconds milliseconds) {
    std::this_thread::sleep_for(milliseconds);
}