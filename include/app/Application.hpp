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
    /**
     * @brief 根据游戏状态改变App运行状态
     */
    void changeState(GameState gameState);
    void changeState(AppState state);
    void processInput();
    void update();
    void render();
    std::chrono::milliseconds getCurrentTime();
    void sleep(std::chrono::milliseconds milliseconds);

public:
    static const int FPS = 5;
    static constexpr std::chrono::milliseconds MS_PER_FRAME = std::chrono::milliseconds(1000 / FPS);

    Application(ConsoleUI& ui, InputDevice& input);
    ~Application() = default;
    GameConfig& getGameConfig();
    const GameConfig& getGameConfig() const;
    std::unique_ptr<Game> initGame(GameConfig config);
    void mainLoop();
    void startGame();
    void exit();
};