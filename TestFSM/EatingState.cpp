//#include "TestDefine.h"
#include "EatingState.h"
#include "GameObject.h"
#include <iostream>

void EatingState::HandleEvent(GameObject& obj, Event e)
{
	if (e == Event::Bored)
	{
		obj.ChangeState(State::Dancing);
	}
}

void EatingState::Update(GameObject& obj)
{
	std::cout << "GameObject is now Eating.\n";
}
