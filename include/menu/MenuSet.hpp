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
        ss << "==================开始菜单====================\n";
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
            .addItem(std::make_unique<MenuEnumItem<AIStrategy>>("玩家1 AI: ",
                [](const Application& app) {
                    return app.getGameConfig().player1Strategy;
                },
                [](Application& app, AIStrategy val) {
                    app.getGameConfig().player1Strategy = val;
                },
                std::vector<AIStrategy>{AIStrategy::RANDOM, AIStrategy::SCORE1, AIStrategy::SCORE2},
                std::vector<std::string>{"随机", "策略1", "策略2"}))
            .addItem(std::make_unique<MenuBoolItem>("玩家2: ",
                [](const Application& app) {
                    return app.getGameConfig().player2IsAI;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().player2IsAI = val;
                }, "AI", "人类"))
            .addItem(std::make_unique<MenuEnumItem<AIStrategy>>("玩家2 AI: ",
                [](const Application& app) {
                    return app.getGameConfig().player2Strategy;
                },
                [](Application& app, AIStrategy val) {
                    app.getGameConfig().player2Strategy = val;
                },
                std::vector<AIStrategy>{AIStrategy::RANDOM, AIStrategy::SCORE1, AIStrategy::SCORE2},
                std::vector<std::string>{"随机", "策略1", "策略2"}))
            .addItem(std::make_unique<MenuBoolItem>("计时器: ",
                [](const Application& app) {
                    return app.getGameConfig().useTimeLimit;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().useTimeLimit = val;
                }, "开", "关"))
            .addItem(std::make_unique<MenuBoolItem>("允许悔棋: ",
                [](const Application& app) {
                    return app.getGameConfig().allowUndo;
                },
                [](Application& app, bool val) {
                    app.getGameConfig().allowUndo = val;
                }, "开", "关"))
            .addItem(std::make_unique<MenuTaskItem>("退出游戏", std::make_unique<ExitTask>()));
        return menu;
    }
};