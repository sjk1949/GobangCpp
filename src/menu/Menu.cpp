#include "menu/Menu.hpp"

#include <sstream>
#include "app/Application.hpp"
#include "command/MenuCommand.hpp"

Menu& Menu::setTitle(std::string title) {
    this->title = std::move(title);
    return *this;
}

Menu& Menu::addItem(std::unique_ptr<MenuItem> item) {
    items.push_back(std::move(item));
    return *this;
}
Menu& Menu::setApp(Application& app) {
    this->app = &app;
    return *this;
}

void Menu::handleInput(std::unique_ptr<MenuCommand> command) {
    command->execute(*this);
}

void Menu::selectNext() {
    selectedItem += 1;
    if (selectedItem >= items.size()) {
        selectedItem = items.size() - 1;
    }
}

void Menu::selectPrev() {
    selectedItem -= 1;
    if (selectedItem < 0) {
        selectedItem = 0;
    }
}

void Menu::confirm() {
    if (!app) {return;}
    items[selectedItem]->onSelected(*app);
}

void Menu::adjust(int dir) {
    if (!app) {return;}
    items[selectedItem]->onAdjust(*app, dir);
}

std::string Menu::toString() const {
    std::stringstream ss;
    ss << title;
    int i = 0;
    for (auto& item : items) {
        ss << i + 1 << ". ";
        if (selectedItem == i) {
            ss << ">";
        } else {
            ss << " ";
        }
        ss << item->toString(*app);
        if (selectedItem == i) {
            ss << "<--selected";
        }
        ss << "\n";
        i++;
    }
    return ss.str();
}