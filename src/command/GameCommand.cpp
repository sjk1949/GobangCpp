#include "command/GameCommand.hpp"

#include "core/Game.hpp"

void PlacePieceCommand::execute(Game& game) {game.placePieceAndCheck(pos);};

void QuitGameCommand::execute(Game& game) {game.quit();};

void InvalidGameCommand::execute(Game& game) {game.recievedInvalidCommand();};
