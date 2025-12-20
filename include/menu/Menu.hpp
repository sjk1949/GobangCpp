#pragma once

#include "utils/Object.hpp"

#include <string>
#include <vector>
#include <memory>
#include "menu/MenuItem.hpp"
#include "command/MenuCommand.hpp"

class Application;

class Menu : public Object
{
private:
    std::vector<std::unique_ptr<MenuItem>> items;
    int selectedItem = 0; // 菜单维护着现在被选中的菜单项
    Application* app = nullptr;

public:
    Menu() = default;
    // 禁止拷贝
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    // 允许移动
    Menu(Menu&&) = default;
    Menu& operator=(Menu&&) = default;
    Menu& addItem(std::unique_ptr<MenuItem> item);
    Menu& setApp(Application& app);
    void handleInput(std::unique_ptr<MenuCommand> command);
    void selectNext();
    void selectPrev();
    void confirm();
    void adjust(int dir);
    std::string toString() const override;
};