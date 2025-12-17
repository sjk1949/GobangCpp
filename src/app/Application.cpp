#include "app/Application.h"

#include "core/Game.h"
#include "player/HumanPlayer.h"
#include "player/AIPlayer.h"

Application::Application(ConsoleUI& ui, InputDevice& input) : ui(ui), input(input) {
    state = AppState::MAIN_MENU;
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

Game Application::initGame(GameConfig config) {
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    if (config.player1IsAI) {
        player1 = std::make_unique<AIPlayer>();
    } else {
        player1 = std::make_unique<HumanPlayer>(input);
    }
    if (config.player2IsAI) {
        player2 = std::make_unique<AIPlayer>();
    } else {
        player2 = std::make_unique<HumanPlayer>(input);
    }
    return Game(std::move(player1), std::move(player2));
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

void Application::runGameLoop(Game game) {
    Board& board = game.getBoard();
    state = AppState::GAME_RUNNING;
    GameState gameState;
    ui.clearScreen();
    ui.displayBoard(board);
    // todo: 这个循环不应只是游戏的循环，而应该修改为应用的大循环，只有AppState = EXIT的条件下才退出
    while (state == AppState::GAME_RUNNING) {
        gameState = game.run();
        ui.clearScreen();
        ui.displayGame(game);
        changeState(gameState);
    }
    switch (gameState)
    {
    case GameState::BLACK_WIN:
        std::cout << "黑棋赢了!" <<std::endl;
        break;
    case GameState::WHITE_WIN:
        std::cout << "白棋赢了!" <<std::endl;
        break;
    default:
        break;
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