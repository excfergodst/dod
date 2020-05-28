#pragma once

#include "Rish/Events/Event.h"

namespace rl {

class RL_API MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x_, float y_)
        : x(x_), y(y_)
    {
    }

    inline std::pair<float, float> getPair() const {
        return std::make_pair(x, y);
    }

    EVENT_CLASS_TOSTRING("MouseMovedEvent: x={:4.2f} y={:4.2f}", x, y)

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

public:
    float x, y;
};

class RL_API MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset_=0.f, float yOffset_=0.f, float x_=0.f, float y_=0.f)
        : xOffset(xOffset_), yOffset(yOffset_), x(x_), y(y_)
    {
    }

    inline std::pair<float, float> getPair() const
    {
        return std::make_pair(xOffset, yOffset);
    }

    EVENT_CLASS_TOSTRING("MouseScrolledEvent: off=({:4.2f},{:4.2f}) pos=({:4.2f},{:4.2f})", xOffset, yOffset, x, y)

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

public:
    float xOffset, yOffset;
    float x, y;
};

/**
 * @brief Mouse Button Event Interface
 * @warning This class is for interface ONLY, do not attempt to construct it
 */
class RL_API MouseButtonEvent : public Event
{
public:
    inline int getMouseButton() const { return button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
    MouseButtonEvent(int btn, int x_, int y_)
        : button(btn), x(x_), y(y_)
    {
    }

public:
    int button;
    int x, y;
};

class RL_API MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int btn, int x_, int y_) : MouseButtonEvent(btn, x_, y_)
    {
    }

    EVENT_CLASS_TOSTRING("MouseButtonPressedEvent: btn={}, ({}, {})", button, x, y)

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class RL_API MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int btn, int x_, int y_) : MouseButtonEvent(btn, x_, y_)
    {
    }

    EVENT_CLASS_TOSTRING("MouseButtonReleasedEvent: btn={}, ({}, {})", button, x, y)

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

}