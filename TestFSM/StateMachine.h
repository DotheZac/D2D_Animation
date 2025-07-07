#pragma once
#include <array>
#include <memory>
#include "IState.h"
//#include "testDefine.h"

template<typename Context>
class StateMachine
{
public:
    StateMachine() = default;

    // �ʱ� ���� �� �� ����
    void Init(State initState)
    {
        m_current = initState;
    }

    State CurrentState() const
    {
        return m_current;
    }

    // ���� �ν��Ͻ� Ǯ ����
    void SetStates(std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)>&& pool)
    {
        states = std::move(pool);
    }

    // ���� ��ȯ
    void ChangeState(State s)
    {
        m_current = s;
    }

    // �̺�Ʈ ����
    void HandleEvent(Context& ctx, Event e)
    {
        states[static_cast<size_t>(m_current)]->HandleEvent(ctx, e);
    }

    // ������Ʈ ����
    void Update(Context& ctx)
    {
        states[static_cast<size_t>(m_current)]->Update(ctx);
    }

private:
    State m_current = State::None;
    std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)> states;
};

