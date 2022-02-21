#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
int main()
{
    /* 시퀀스 컨테이너 (Sequence Container)
    데이터가 삽인 순서대로 나열되는 형태
    (vector, list, deque)

    vector : 동적 배열
    [            ]

    list : 이중 연결 리스트
    [] <-> [] <-> [] <->

    deque : double-ended queue (데크)
    [    ]
    [    ]
    */



    // vector와 마찬가지로 배열 기관으로 동작
    // 다만 메모리 할당 정책이 다르다
    // vector
    // [   기존   ]  여유     ]

    // deque 기존 상자가 꽉차면 통이 여러가지로 나뉜다.
    // [      3, 3]
    // [1, 1, 1, 2]
    // [2         ]

    vector<int> v(3, 1);
    deque<int> dq(3, 1);

    v.push_back(2);
    v.push_back(2);
    dq.push_back(2);
    dq.push_back(2);

    dq.push_front(3);
    dq.push_front(3);

    /* - deque 의 동작 원리
    - 중간 삽입/삭제 (BAD / BAD) -> vector 와 마찬가지로 다른 데이터들을 움직여야한다.
    - 처음/끝 삽입/삭제 (GOOD / GOOD)
    - 임의 접근 (GOOD)
    */

    deque<int>::iterator it;
    /*
    _Size_type _Block = _Mycont->_Getblock(_Myoff);
            _Size_type _Off   = _Myoff % _DEQUESIZ; (_DEQUESIZ = % 4로 사용했다)
            return _Mycont->_Map[_Block][_Off]; (몇동 몇호로 갈것인가, 절대로 중간에 빈값이 있으면 안된다)

    [      3, 3] 1동
    [1, 1, 1, 2] 2동
    [2         ] 3동
    -> 임의 접근 (GOOD)
    */


    return 0;
}