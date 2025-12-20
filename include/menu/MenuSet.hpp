#pragma once

#include <memory>
#include "menu/Menu.hpp"
#include "task/Task.hpp"

class MenuSet
{
public:
    static Menu createMainMenu() {
        Menu menu;
        menu.addItem(std::make_unique<MenuTaskItem>("开始游戏", std::make_unique<StartGameTask>()))
            .addItem(std::make_unique<MenuTaskItem>("加载游戏"))
            .addItem(std::make_unique<MenuValItem<bool>>("玩家1: ",
                [](const Application& app) {
                    return app.getGameConfig().player1IsAI;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().player1IsAI = val;
                },
                [](const bool& val) {
                    return (val == true) ? "AI" : "人类";
                }))
            .addItem(std::make_unique<MenuTaskItem>("退出游戏", std::make_unique<ExitTask>()));
        return menu;
    }
};