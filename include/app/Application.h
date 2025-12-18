#pragma once

#include <chrono>
#include "ui/ConsoleUI.h"
#include "input/InputDevice.h"
#include "core/Game.h"

enum class AppState
{
    MAIN_MENU,
    GAME_RUNNING,
    GAME_OVER,
    EXIT
};

class Application
{
private:
    int i = 0;
    std::chrono::steady_clock::time_point initTime;
    AppState state;
    std::unique_ptr<Game> game;
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
    static const int FPS = 10;
    static constexpr std::chrono::milliseconds MS_PER_FRAME = std::chrono::milliseconds(1000 / FPS);

    Application(ConsoleUI& ui, InputDevice& input);
    ~Application() = default;
    GameConfig getGameConfig();
    std::unique_ptr<Game> initGame(GameConfig config);
    void mainLoop();
    void runGameLoop(Game game);
};