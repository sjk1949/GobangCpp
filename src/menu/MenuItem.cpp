#include "menu/MenuItem.hpp"

#include <sstream>
#include "app/Application.hpp"
#include "task/Task.hpp"

std::string MenuItem::toString() const {return text;}

std::string MenuItem::toString(const Application& app) const {return toString();}

MenuTaskItem::MenuTaskItem(std::string text, std::shared_ptr<Task> taskPtr) : MenuItem(text), task(std::move(taskPtr)) {}

void MenuTaskItem::onSelected(Application& app) {if(!task) {return;} task->execuate(app);}

void MenuTaskItem::onAdjust(Application& app, int dir) {}