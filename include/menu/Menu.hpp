#pragma once

#include "utils/Object.hpp"

#include <string>
#include <vector>
#include <memory>
#include "task/Task.hpp"

class MenuItem : public Object
{
public:
    MenuItem(std::string text, std::shared_ptr<Task> taskPtr = nullptr) : text(text), task(std::move(taskPtr)) {};
    std::string toString() const override {return text;};
    void onSelected() {if(!task) {return;} task->execuate();};

private:
    std::string text;
    std::shared_ptr<Task> task;
};

class Menu : public Object
{
private:
    std::vector<MenuItem> items;
    int selectedItem = 0; // 菜单维护着现在被选中的菜单项

public:
    Menu() = default;
    Menu& addItem(MenuItem&& item);
    void selectNext();
    void selectPrev();
    void confirm();
    std::string toString() const override;
};