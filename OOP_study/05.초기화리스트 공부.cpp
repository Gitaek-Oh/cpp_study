#include <iostream>
using namespace std;

/*
초기화 해야하는 이유
- 버그 예방에 중요하다
- 포인터 등 주소값이 연루되어 있을 경우

초기화 방법
- 생성자 내에서 초기화

- 초기화 리스트
-- 상속 관계에서 원하는 부모 생성자를 호출할 때 필요하다.
-- 생성자 내에서 초기화 vs 초기화 리스트
--- 일반 변수는 별 차이 없음
--- 멤버 타입이 클래스인 경우 차이가 난다.
--- 정의함과 동시에 초기화가 필요한 경우(참조 타입, const 탑입)

- C++11 문법
*/
class Inventory
{
public:
	Inventory() { cout << "Inventory()" << endl; }
	Inventory(int size) { cout << "Inventory(int size)" << endl; }

	~Inventory() { cout << "~Inventory()" << endl; }
};

class Player
{
public:
	Player() { }
	Player(int id) { }
};


class Knight : public Player // 부모의 기본생성자를 호출한다
{
public:
	Knight() : Player(1), _hp(100), _inventory(20), _hpRef(_hp), _hpConst(100) //부모의 다른 버전의 생성자,초기화 리스트 -> 선처리 영역에서 초기화 리스트를 사용하는 것이 좋다.
	/*

	선처리 영역
	Inventory() -> 기본생성자 호출

	*/
	{
		_hp = 100;
		//_inventory = Inventory(20); // 선처리 영역에서 인벤토리가 만들어져 있는데  여기에서 또 만들어져서 2번 호출하게 된다.
		 //따라서 위에 있는 내용처럼 써줘야 된다.(_inventory(20))

		//위에 초기화리스트에 추가해 주면된다, C++11문법은
		//_hpRef = _hp; //참조타입으로 누군가는 가르키고 있어야 한다.
		//_hpConst = 100;
	}
public:
	int _hp;
	//int _attack = 100; // C++11 문법
	Inventory _inventory;

	int& _hpRef; //참조타입으로 누군가는 가르키고 있어야 한다.
	const int _hpConst;

	//C++11문법은 아래와 같이 해주면 된다
	//int& _hpRef = 100; //참조타입으로 누군가는 가르키고 있어야 한다.
	//const int _hpConst = 100;
};

int main()
{
	Knight k;


	cout << k._hp << endl;

	return 0;
}
