#pragma once

#include <array>
#include <memory>
#include "IState.h"
#include "TestDefine.h"
#include "StateMachine.h"

/// <summary>
///  FSM�� ����� GameObject�� ���� 
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
    // State::Count ��ŭ ���� �ν��Ͻ� ����
    //std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)> m_states;
    //IState* m_currentState = nullptr;
    StateMachine<GameObject> m_sm;
};