#include "menu/Menu.hpp"

#include "app/Application.hpp"
#include "task/Task.hpp"

MenuItem::MenuItem(std::string text, std::shared_ptr<Task> taskPtr) : text(text), task(std::move(taskPtr)) {};

void MenuItem::onSelected(Application& app) {if(!task) {return;} task->execuate(app);};

std::string MenuItem::toString() const {return text;};