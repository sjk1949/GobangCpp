#include "command/MenuCommand.hpp"
#include "menu/Menu.hpp"

void MoveUpCommand::execute(Menu& menu) {menu.selectPrev();};

void MoveDownCommand::execute(Menu& menu) {menu.selectNext();};

void ConfirmCommand::execute(Menu& menu) {menu.confirm();};