#pragma once

#include <string>
#include <cstdint>

class Object
{
private:
    /* data */
public:
    virtual ~Object() = default;
    virtual std::string toString() const {
        return "Object@" + std::to_string(reinterpret_cast<std::uintptr_t>(this));
    };
};