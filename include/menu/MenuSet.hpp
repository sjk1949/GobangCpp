#pragma once

#include <sstream>
#include <memory>
#include "menu/Menu.hpp"
#include "menu/MenuItemFactory.hpp"
#include "task/Task.hpp"

class MenuSet
{
public:
    static Menu createMainMenu() {
        Menu menu;
        std::stringstream ss;
        ss << "======================================\n";
        ss << "=             五子棋小游戏            =\n";
        ss << "=               @copyright           =\n";
        ss << "======================================\n";
        ss << "==============开始菜单================\n";
        menu.setTitle(ss.str())
            .addItem(std::make_unique<MenuTaskItem>("开始游戏", std::make_unique<StartGameTask>()))
            .addItem(std::make_unique<MenuTaskItem>("加载游戏"))
            .addItem(std::make_unique<MenuBoolItem>("玩家1: ",
                [](const Application& app) {
                    return app.getGameConfig().player1IsAI;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().player1IsAI = val;
                }, "AI", "人类"))
            .addItem(std::make_unique<MenuBoolItem>("玩家2: ",
                [](const Application& app) {
                    return app.getGameConfig().player2IsAI;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().player2IsAI = val;
                }, "AI", "人类"))
            .addItem(std::make_unique<MenuBoolItem>("计时器: ",
                [](const Application& app) {
                    return app.getGameConfig().useTimeLimit;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().useTimeLimit = val;
                }, "开", "关"))
            .addItem(std::make_unique<MenuTaskItem>("退出游戏", std::make_unique<ExitTask>()));
        return menu;
    }
};