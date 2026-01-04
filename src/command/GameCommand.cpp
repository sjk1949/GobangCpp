#include "command/GameCommand.hpp"

#include "core/Game.hpp"

void PlacePieceCommand::execute(Game& game) {game.placePieceAndCheck(pos);}

void UndoCommand::execute(Game& game) {game.undoLastMove();}

void QuitGameCommand::execute(Game& game) {game.quit();}

void HelpCommand::execute(Game& game) {game.showHelp();}

void InvalidGameCommand::execute(Game& game) {game.recievedInvalidCommand();}
