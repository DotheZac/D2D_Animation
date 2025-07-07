//#include "TestDefine.h"
#include "SleepingState.h"
#include "GameObject.h"
#include <iostream>

void SleepingState::HandleEvent(GameObject& obj, Event e)
{
    if (e == Event::Hungry)
    {
        obj.ChangeState(State::Eating);
    }
}

void SleepingState::Update(GameObject& obj)
{
    std::cout << "GameObject is now Sleeping.\n";
}