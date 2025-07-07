#include "GameObject.h"
#include "EatingState.h"
#include "DancingState.h"
#include "SleepingState.h"
#include <iostream>


GameObject::GameObject()
{
    std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)> states
        = {std::make_shared<EatingState>(), 
        std::make_shared<DancingState>(),
        std::make_shared<SleepingState>(),
    std::make_shared<SleepingState>() };
    
    m_sm.SetStates(std::move(states));

    ChangeState(State::Sleeping);
}

void GameObject::ChangeState(State newState)
{
    // (필요 시) 이전 상태 Exit 콜백 등을 추가
    //m_currentState = m_states[static_cast<size_t>(newState)].get();
    // (필요 시) Enter 콜백 등을 추가
    m_sm.ChangeState(newState);
}

void GameObject::HandleEvent(Event e)
{
    //if (m_currentState)
    //    m_currentState->HandleEvent(*this, e);
    if (m_sm.CurrentState() != State::None)
    {
        m_sm.HandleEvent(*this, e);
    }
}

void GameObject::Update()
{
    if (m_sm.CurrentState() != State::None)
    {
        m_sm.Update(*this);
    }
}
