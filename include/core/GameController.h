#pragma once

#include "ui/ConsoleUI.h"
#include "input/InputDevice.h"
#include "core/Game.h"

enum class GameControllerState
{
    START_GAME,
    MAIN_MENU
};

class GameController
{
private:
    GameControllerState state;
    ConsoleUI& ui;
    InputDevice& input;

    GameConfig createDefaultConfig();

public:
    GameController(ConsoleUI& ui, InputDevice& input);
    ~GameController() = default;
    GameConfig getGameConfig();
    Game initGame(GameConfig config);
    void runGameLoop(Game game);
};