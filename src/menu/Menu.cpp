#include "menu/Menu.hpp"

#include <sstream>

Menu& Menu::addItem(MenuItem&& item) {
    items.push_back(std::move(item));
    return *this;
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
    items[selectedItem].onSelected();
}

std::string Menu::toString() const {
    std::stringstream ss;
    int i = 0;
    for (auto& item : items) {
        ss << i + 1 << ". " << item.toString();
        if (selectedItem == i) {
            ss << "<--selected";
        }
        ss << "\n";
        i++;
    }
    return ss.str();
}