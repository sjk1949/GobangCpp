#pragma once

#include <memory>
#include "menu/Menu.hpp"

class MenuSet
{
public:
    inline static Menu mainMenu = Menu().
        addItem(MenuItem("开始游戏", std::make_unique<StartGameTask>()))
        .addItem(MenuItem("退出游戏", std::make_unique<ExitTask>()));
};