#pragma once

#include "utils/Object.hpp"

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <sstream>
#include "command/MenuCommand.hpp"

class Application;
class Task;

class MenuItem : public Object
{
public:
    MenuItem(std::string text) : text(text) {};
    virtual ~MenuItem() = default;
    virtual void onSelected(Application& app) = 0;
    virtual void onAdjust(Application& app, int dir) = 0;
    virtual std::string toString(const Application& app) const;
    std::string toString() const override;
    

protected:
    std::string text;
};

class MenuTaskItem : public MenuItem
{
public:
    MenuTaskItem(std::string text, std::shared_ptr<Task> taskPtr = nullptr);
    void onSelected(Application& app) override;
    void onAdjust(Application& app, int dir) override;

protected:
    std::shared_ptr<Task> task;
};

template <class T>
class MenuValItem : public MenuItem
{
public:
    using Getter = std::function<T(const Application&)>;
    using Setter = std::function<void(Application&, const T&)>;
    using Formatter = std::function<std::string(const T&)>;

    MenuValItem(std::string text, Getter getter, Setter setter, Formatter formatter)
        : MenuItem(std::move(text))
        , getter(std::move(getter))
        , setter(std::move(setter))
        , formatter(std::move(formatter))
    {};
    void onSelected(Application& app) override {};
    void onAdjust(Application& app, int dir) override {};
    std::string toString(const Application& app) const override {
        std::stringstream ss;
        ss << text << formatter(getter(app));
        return ss.str();
    };

protected:
    Getter getter;
    Setter setter;
    Formatter formatter;
};

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
    std::string toString() const override;
};