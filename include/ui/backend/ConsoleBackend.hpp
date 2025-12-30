#pragma once
#include <string>

/**
 * @interface ConsoleBackend
 * @brief Abstract interface for platform-specific console rendering backends.
 *
 * Concrete implementations (e.g., ANSI-based, Win32-based) may differ
 * significantly in rendering strategy and platform constraints.
 *
 * The backend abstraction was designed to allow flexible backend
 * selection at runtime based on the detected terminal environment.
 */
class ConsoleBackend {
public:
    virtual ~ConsoleBackend() = default;

    virtual void beginFrame() = 0;
    virtual void draw(const std::string& utf8Text) = 0;
    virtual void endFrame() = 0;

    virtual void onResize() = 0;
};
