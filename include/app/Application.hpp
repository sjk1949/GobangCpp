#pragma once

#include <chrono>
#include "ui/ConsoleUI.hpp"
#include "input/InputDevice.hpp"
#include "core/Game.hpp"
#include "menu/Menu.hpp"
#include "input/InputContext.hpp"

class Menu;

enum class AppState
{
    MAIN_MENU,
    GAME_RUNNING,
    EXIT
};

class Application
{
private:
    bool debugMode;
    int frame = 0;
    std::chrono::steady_clock::time_point initTime;
    AppState state;
    std::unique_ptr<Game> game;
    Menu menu;
    GameConfig gameConfig;
    std::string inputBuffer = "";
    std::unique_ptr<InputContext> inputContext;
    ConsoleUI& ui;
    InputDevice& input;

    GameConfig createDefaultConfig();
    void changeState(AppState state);
    void processInput();
    void update();
    void render();
    std::chrono::milliseconds getCurrentTime();
    void sleep(std::chrono::milliseconds milliseconds);

public:
    static const int FPS = 20;
    static constexpr std::chrono::milliseconds MS_PER_FRAME = std::chrono::milliseconds(1000 / FPS);

    Application(ConsoleUI& ui, InputDevice& input, bool debugMode = false);
    ~Application() = default;
    GameConfig& getGameConfig();
    const GameConfig& getGameConfig() const;
    void mainLoop();
    void startGame();
    void exit();
};