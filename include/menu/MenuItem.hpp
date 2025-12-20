#pragma once

#include "utils/Object.hpp"

#include <string>
#include <memory>
#include <functional>
#include <sstream>

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
    using Adjuster = std::function<T(const T&, int)>;
    using Formatter = std::function<std::string(const T&)>;

    MenuValItem(std::string text, Getter getter, Setter setter, Adjuster adjuster, Formatter formatter)
        : MenuItem(std::move(text))
        , getter(std::move(getter))
        , setter(std::move(setter))
        , adjuster(std::move(adjuster))
        , formatter(std::move(formatter))
    {};
    void onSelected(Application& app) override {};
    void onAdjust(Application& app, int dir) override {
        T originVal = getter(app);
        setter(app, adjuster(originVal, dir));
    };
    std::string toString(const Application& app) const override {
        std::stringstream ss;
        ss << text << formatter(getter(app));
        return ss.str();
    };

protected:
    Getter getter;
    Setter setter;
    Adjuster adjuster;
    Formatter formatter;
};