#pragma once

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
    AppState state;
    ConsoleUI& ui;
    InputDevice& input;

    GameConfig createDefaultConfig();
    /**
     * @brief 根据游戏状态改变App运行状态
     */
    void changeState(GameState gameState);

public:
    Application(ConsoleUI& ui, InputDevice& input);
    ~Application() = default;
    GameConfig getGameConfig();
    Game initGame(GameConfig config);
    void runGameLoop(Game game);
};