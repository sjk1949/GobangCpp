#pragma once

#include <memory>
#include "menu/MenuItem.hpp"

class MenuItemFactory
{
public:
    using Getter = std::function<bool(const Application&)>;
    using Setter = std::function<void(Application&, const bool&)>;
    static std::unique_ptr<MenuValItem<bool>> makeBool(std::string text, Getter getter, Setter setter, std::string on, std::string off) {
        return std::make_unique<MenuValItem<bool>>(text, getter, setter,
        [](const bool& originVal, int dir) {
            return !originVal;
        },
        [on, off](const bool& val) {
            return (val == true) ? on : off;
        });
    }
};