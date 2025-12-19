#pragma once

#include "utils/Object.hpp"

#include <string>
#include <vector>
#include <memory>
#include "command/MenuCommand.hpp"

class Application;
class Task;

class MenuItem : public Object
{
public:
    MenuItem(std::string text, std::shared_ptr<Task> taskPtr = nullptr);
    std::string toString() const override;
    void onSelected(Application& app);

private:
    std::string text;
    std::shared_ptr<Task> task;
};

class Menu : public Object
{
private:
    std::vector<MenuItem> items;
    int selectedItem = 0; // 菜单维护着现在被选中的菜单项
    Application* app = nullptr;

public:
    Menu() = default;
    Menu& addItem(MenuItem&& item);
    Menu& setApp(Application& app);
    void handleInput(std::unique_ptr<MenuCommand> command);
    void selectNext();
    void selectPrev();
    void confirm();
    std::string toString() const override;
};