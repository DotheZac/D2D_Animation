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

    // 초기 상태 한 번 설정
    void Init(State initState)
    {
        m_current = initState;
    }

    State CurrentState() const
    {
        return m_current;
    }

    // 상태 인스턴스 풀 세팅
    void SetStates(std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)>&& pool)
    {
        states = std::move(pool);
    }

    // 상태 전환
    void ChangeState(State s)
    {
        m_current = s;
    }

    // 이벤트 위임
    void HandleEvent(Context& ctx, Event e)
    {
        states[static_cast<size_t>(m_current)]->HandleEvent(ctx, e);
    }

    // 업데이트 위임
    void Update(Context& ctx)
    {
        states[static_cast<size_t>(m_current)]->Update(ctx);
    }

private:
    State m_current = State::None;
    std::array<std::shared_ptr<IState>, static_cast<size_t>(State::Count)> states;
};

