#include "command/GameCommand.h"

#include "core/Game.h"

void PlacePieceCommand::execute(Game& game) {game.placePieceAndCheck(pos);};

void QuitGameCommand::execute(Game& game) {game.quit();};

void InvalidGameCommand::execute(Game& game) {game.recievedInvalidCommand();};
