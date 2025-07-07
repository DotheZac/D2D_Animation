#pragma once

#include <array>
#include <memory>
#include "IState.h"
#include "TestDefine.h"
#include "StateMachine.h"

/// <summary>
///  FSM을 사용한 GameObject의 예시 
/// </summary>



class GameObject
{
public:
    GameObject();
    ~GameObject() = default;

    void HandleEvent(Event e);
    void Update();

    void ChangeState(State newState);

    void OnEnter(State s) {}
    void OnExit(State s) {}

private:
    // State::Count 만큼 상태 인스턴스 보관
    //std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)> m_states;
    //IState* m_currentState = nullptr;
    StateMachine<GameObject> m_sm;
};