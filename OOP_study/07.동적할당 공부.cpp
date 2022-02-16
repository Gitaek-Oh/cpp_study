#include <iostream>
using namespace std;

/*
메모리 구조 복습
- 실행할 코드가 저장되는 영역 -> 코드영역
- 전역(global) / 정적(static) 변수 -> 데이터 영역
- 지역 변수 / 매개 변수 -> 스택 영역
- 동적 할당 -> 힙 영역

지금까지 데이터 영역 / 스택 영역 이용해서 잘 만들어 왔는 데 굳이 새로운 영역이 필요한가?

실제 상황)
 - MMORPG 동접 1명 ~ 5만명, 몬스터 1마리 ~ 500만마리
 - 몬스터 생성 이벤트 -> 5분동안 몬스터가 10배 많이 나옴 -> 항상 최대 상한선을 늘려서 만들 수가 없어서 문제가 생긴다.

 - 스택 영역
 함수가 끝나면 같이 정리되는 불안정한 메모리
 잠시 함수에 매개변수 넘긴다거나 하는 용도로는 OK
 - 메모리 영역
 프로그램이 실행되는 도중에는 '무조건' 사용됨...

 희망사항)
  - 필요할 때만 사용하고, 필요없으면 반납할 수 있는..!
  - 그러면서도 (스택과 다르게) 우리가 생성/소명 시점을 관리할 수 있는!
  -> HEAP!!

 동적할당과 연관된 함수/연산자 : malloc / free, new / delete, new[] / delete[]

* malloc
할당할 메모리 크기를 건내준다.
메모리 할당 후 시작 주소를 가리키는 포인터를 반환해준다 (메모리 부족하다 싶으면 NULL 포인터를 반환)
* free
malloc (혹은 기타 calloc, realloc 등의 사촌)을 통해 할당된 영역을 해제
힙 관리자가 할당/미할당 여부를 구분해서 관리

* new / delete
- C++에 추가됨
- malloc/free 함수! new/delete는 연산자!(operator)

* new[] delete[]
- new가 malloc에 비해 좋긴 한데 배열과 같이 N개 데이터를 같이 할당하려면? new/delete는 불가능하지만 배열버전은 가능하다.

malloc/free vs new/delete
- 사용편의성 ->new/delete 가 승!
- 타입에 상관없이 특정한 크기의 메모리 영역을 할당받으려면 -> malloc / free 승!

그런데 둘의 가장 큰본적인 중요한 차이는 따로 있다!
new / delete는 (생성타입이 클래스일 경우) 생성자와 소멸자를 호출해준다! -> malloc은 c언어에서 생성된 개념이기에 메모리만 할당해준다
*/

class Monster
{
public:
	Monster()
	{
		cout << "Monster()" << endl;
	}
	~Monster()
	{
		cout << "~Monster()" << endl;
	}
public:
	int _hp;
	int _x;
	int _y;
};


//Monster monster[500 * 10000]; //실행은 되지만 메모리 낭비가 될 수 있다 -> ex) 동접이 1명인데 몬스터가 500만마리 -> 비효율적이다

int main()
{
	//Monster monster[500 * 10000]; //스택은 많은 데이터를 저장하는 용도가 아니라 함수들 끼리 인자를 주고받는 용도로 만들어졌기 때문에 오버플로우가 뜨게된다.

	/*
	유저 영역 (메모장,LOL,곰플레이어 등등)
	-------------------------------------------
	커널 영역 (Windows 등의 핵심 코드)

	유저 영역) 운영체제에서 제공하는 API 호출
	커널 영역) 메모리 할당해서 건내줌
	유저 영역) 잘 쓸게요~

	C++에서는 기본적으로 CRT(C런타임 라이브러리)의 [힙 관리자]를 통해 힙 영역 사용
	단, 정말 원한다면 우리가 직접 API를 통해 입을 생성하고 관리할 수도 있음 (MMORPG 서버 메모리 폴링)
	*/

	/*
	* size_t를 F12를 눌러서 정의를 확인
	#ifdef _WIN64
	typedef unsigned __int64 size_t;
	#else
	typedef unsigned int     size_t;
	#endif
	typedef a b -> a를 b의 이름으로 정의하겠다.
	*/

	/*
	void* 는 무엇인가?
	*가 있으니까 포인터는 포인터 (주소를 담는 바구니)
	타고가면 void, 아무것도 없다? -> X
	타코가면 void, 뭐가 있는지 모르겠으니까 너가 적당히 변환해서 사용해라 -> OK
	*/
	void* pointer = malloc(sizeof(Monster)); // 기본적인 동적할당 구조, 메모리 낭비는 없어질 것이다.

	Monster* m1 = (Monster*)pointer; // cdcd쓰레기 값이 들어갔다....
	m1->_hp = 100;
	m1->_x = 1;
	m1->_y = 2;

	//Heap Overflow: 유효한 힙 범위를 초과해서 사용하는 문제 (malloc의 범위를 작게 했을 때)

	//free를 안해 반환을 안해 줄 경우 메모리 누수가 생겨 점점점 쌓이면서 시스템이 누워버릴 수 있다.
	free(pointer); //메모리가 필요없어졌을 때 메모리 해제

	// 더이상 사용하지 않는다는 nullptr로 밀어주면 메모리 오류의 예방이 가능하다.
	pointer = nullptr;
	m1 = nullptr;

	// Double Free
	// 이건 대부분 그냥 크래시만 나고 끝난다.
	//free(pointer);

	// USE-AFTER-FREE (사용을 하고 free로 해줬는 데 다시 사용하는 경우)
	//- 프로그래머 입장 : OMG 망했다! 문제를 찾기도 힘들어서 조심해야 된다.
	//- 해커 입장 : 심봤다!
	//m1->_hp = 100;
	//m1->_x = 1;
	//m1->_y = 2;

	Monster* m2 = new Monster;
	m2->_hp = 200;
	m2->_x = 2;
	m2->_y = 3;
	delete m2; // Double Free, USE-AFTER-FREE 상황이 공통적으로 있다.
	// -> new / delete는 한마리만 만드는 데 사용되기 때문에 아쉬운 부분이 있다.
	// dddddddd 로 메모리가 날라간다.

	Monster* m3 = new Monster[5]; // 몬스터 하나당 12바이트이기 때문에 0x3c(60)값이 들어가게 된다. , (Monster(생성자) * 5, ~Monster(소멸자) * 5) 가 만들어진다.
	m3->_hp = 200;
	m3->_x = 2;
	m3->_y = 3;
	delete[] m3; // 배열로 똑같이 만들어줘야 한다.
	// -> 배열로 여러개 만들 수 있다, Double Free, USE-AFTER-FREE 상황이 공통적으로 있다.



	return 0;
}
