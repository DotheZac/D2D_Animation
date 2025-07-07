#pragma once
#include "IState.h"
class DancingState : public IState
{
public:
    void HandleEvent(GameObject& obj, Event e) override;
    void Update(GameObject& obj) override;
};

