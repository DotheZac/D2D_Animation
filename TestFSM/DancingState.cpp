//#include "TestDefine.h"
#include "DancingState.h"
#include "GameObject.h"
#include <iostream>

void DancingState::HandleEvent(GameObject& obj, Event e)
{
	if (e == Event::Hungry)
	{
		obj.ChangeState(State::Eating);
	}
	else if (e == Event::Tired)
	{
		obj.ChangeState(State::Sleeping);
	}
}

void DancingState::Update(GameObject& obj)
{
	std::cout << "GameObject is now Dancing.\n";
}
