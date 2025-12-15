#include "core/GameController.h"

#include "core/Game.h"
#include "player/HumanPlayer.h"
#include "player/AIPlayer.h"

GameController::GameController(ConsoleUI& ui, InputDevice& input) : ui(ui), input(input) {
    state = GameControllerState::MAIN_MENU;
}

GameConfig GameController::getGameConfig() {
    GameConfig config = createDefaultConfig();
    bool isAI;
    isAI = input.getInput("Player1 AI(0/1)?") == "1";
    config.player1IsAI = isAI;
    isAI = input.getInput("Player2 AI(0/1)?") == "1";
    config.player2IsAI = isAI;
    return config;
}

Game GameController::initGame(GameConfig config) {
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
Game GameController::initGame() {
    GameConfig config = createDefaultConfig();
    while (state == GameControllerState::MAIN_MENU) {
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

void GameController::runGameLoop(Game game) {
    Board& board = game.getBoard();
    GameState state = GameState::PLAYING;
    ui.clearScreen();
    ui.displayBoard(board);
    while (state == GameState::PLAYING) { 
        state = game.run();
        ui.clearScreen();
        ui.displayBoard(board);
        std::string& message = game.getMessage();
        if (!message.empty()) {
            ui.print(message);
            message.clear();
        }
    }
    switch (state)
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

GameConfig GameController::createDefaultConfig() {
    return GameConfig();
}