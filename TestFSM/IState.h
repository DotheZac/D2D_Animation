#pragma once

class GameObject;
enum class Event;

class IState
{
public:
    virtual ~IState() = default;

    virtual void HandleEvent(GameObject& obj, Event e) = 0;
    virtual void Update(GameObject& obj) = 0;
};