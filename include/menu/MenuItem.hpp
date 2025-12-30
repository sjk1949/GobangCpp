#pragma once

#include "utils/Object.hpp"

#include <string>
#include <memory>
#include <functional>
#include <sstream>
#include <algorithm>
#include <cassert>

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

class MenuBoolItem : public MenuValItem<bool>
{
public:
    using Getter = std::function<bool(const Application&)>;
    using Setter = std::function<void(Application&, const bool&)>;
    MenuBoolItem(std::string text, Getter getter, Setter setter, std::string on, std::string off);
    void onSelected(Application& app) override;
};

template <typename Enum>
class MenuEnumItem : public MenuValItem<Enum>
{
public:
    using Getter = std::function<Enum(const Application&)>;
    using Setter = std::function<void(Application&, const Enum&)>;

    MenuEnumItem(
        std::string text,
        Getter getter,
        Setter setter,
        std::vector<Enum> values,
        std::vector<std::string> labels
    )
        : MenuValItem<Enum>(std::move(text), getter, setter,
        [values](const Enum& originVal, int dir) {
            auto it = std::find(values.begin(), values.end(), originVal);
            if (it == values.end()) return originVal;;

            size_t idx = std::distance(values.begin(), it);
            idx = (idx + dir + values.size()) % values.size();
            return values[idx];
        },
        [values, labels](const Enum& val) {
            auto it = std::find(values.begin(), values.end(), val);
            if (it == values.end()) return std::string("<?>");

            size_t idx = std::distance(values.begin(), it);
            return labels[idx];
        })
        , values(std::move(values))
        , labels(std::move(labels))
    {
        assert(this->values.size() == this->labels.size());
    }

    void onSelected(Application& app) override
    {
        this->onAdjust(app, +1);
    }

private:
    std::vector<Enum> values;
    std::vector<std::string> labels;
};