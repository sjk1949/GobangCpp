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

Application::Application(ConsoleUI& ui, InputDevice& input) : ui(ui), input(input) {
    state = AppState::MAIN_MENU;
    menu = MenuSet::mainMenu;
    initTime = std::chrono::steady_clock::now();
    inputContext = std::make_unique<MenuInputContext>();
}

GameConfig Application::getGameConfig() {
    GameConfig config = createDefaultConfig();
    bool isAI;
    isAI = input.getInput("Player1 AI(0/1)?") == "1";
    config.player1IsAI = isAI;
    isAI = input.getInput("Player2 AI(0/1)?") == "1";
    config.player2IsAI = isAI;
    return config;
}

std::unique_ptr<Game> Application::initGame(GameConfig config) {
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    if (config.player1IsAI) {
        player1 = std::make_unique<AIPlayer>();
    } else {
        player1 = std::make_unique<HumanPlayer>();
    }
    if (config.player2IsAI) {
        player2 = std::make_unique<AIPlayer>();
    } else {
        player2 = std::make_unique<HumanPlayer>();
    }
    return std::make_unique<Game>(std::move(player1), std::move(player2));
}

/*
Game Application::initGame() {
    GameConfig config = createDefaultConfig();
    while (state == ApplicationState::MAIN_MENU) {
        ui.displayStartMenu(config);
        InputResult result = input.getMenuInput();
        switch (result.command)
        {
        case InputCommand::SELECT_FROM_MENU:
            break;
        }
    }
}
*/

void Application::mainLoop() {
    //game = initGame(getGameConfig());
    //changeState(AppState::GAME_RUNNING);
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

void Application::changeState(GameState gameState) {
    if (gameState == GameState::PLAYING) {
        state = AppState::GAME_RUNNING;
    } else {
        state = AppState::GAME_OVER;
    }
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
    if (state == AppState::GAME_RUNNING) {
        game->update();
        changeState(game->getGameState());
    } else if (state == AppState::GAME_OVER) {
        changeState(AppState::EXIT);
    }
}

void Application::render() {
    ui.clear();
    if (state == AppState::MAIN_MENU) {
        ui.displayMenu(menu);
    } else if (state == AppState::GAME_RUNNING) {
        ui.displayGame(*game);
        ui.print(inputContext->getBuffer(), "\n");
        ui.print("Frame: ", frame, "\n");
    } else if (state == AppState::GAME_OVER) {
        ui.displayGame(*game);
        ui.displayGameResult(game->getGameState());
    } else if (state == AppState::EXIT) { // 应用退出的时候不再刷新屏幕
        return;
    }
    ui.drawDebugPanel();
    ui.flip();
}

std::chrono::milliseconds Application::getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - initTime);
}

void Application::sleep(std::chrono::milliseconds milliseconds) {
    std::this_thread::sleep_for(milliseconds);
}