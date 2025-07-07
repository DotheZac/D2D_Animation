#include <iostream>
//#include "TestDefine.h"
//#include "SimpleCase.h"
#include "GameObject.h"


int main()
{
    //TestObject gameObject;
    GameObject gameObject;


    //상태 전환을 테스트을 위한 이벤트 루프
    while (true)
    {
        // 이벤트를 처리하기 위한 예시 입력
        char input;
        std::cout << "Enter event (h: Hungry, b: Bored, t: Tired, q: Quit): ";
        std::cin >> input;

        if (input == 'q') break; // 'q' 입력 시 종료

        Event event;

        switch (input)
        {
        case 'h':
            event = Event::Hungry;
            break;
        case 'b':
            event = Event::Bored;
            break;
        case 't':
            event = Event::Tired;
            break;
        default:
            continue; // 잘못된 입력은 무시
        }

        gameObject.HandleEvent(event);
        gameObject.Update();
    }

    return 0;
}
