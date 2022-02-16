#include <iostream>
using namespace std;

void HelloWorld()
{
	cout << "Hello World" << endl;
}

void HelloNumber(int number)
{
	cout << "Hello Number" << number << endl;
}

class Knight
{
public:
	void AddHp(int addHp)
	{
		_hp += addHp;
	}
private:
	int _hp = 100;
};

class Functor
{
public:
	void operator() ()
	{
		cout << "Functor Test" << endl;
		cout << _value << endl;
	}

	bool operator()(int num)
	{
		cout << "Functor Test" << endl;
		_value += num;
		cout << _value << endl;

		return true;
	}
private:
	int _value = 0;
};

class MoveTask
{
public:
	void operator() ()
	{
		//TODO
		cout << "해당 좌표로 플레이어 이동" << endl;
	}
public:
	int _playerId;
	int _posX;
	int _posY;
};

int main()
{
	/* 함수 객체 (Functor) : 함수처럼 동작하는 객체
	 함수 포인터의 단점 : 완전히 동일한 시그니처의 함수만 포인터로 들고 있을 수 있다.
	 -> 이걸 함수 객체를 이용하면 어느정도 극복을 할 수 있다.

	 함수 포인터 복습
	 함수 포인터 선언
	*/

	void (*pfunc)(void);
	// 동작을 넘겨줄 때 유용하다.
	pfunc = &HelloWorld;
	(*pfunc)();

	/* 함수 포인터의 단점
	 1) 시그니처가 안 맞으면 사용할 수 없다.
	 pfunc = &HelloNumber; -> 오류가 발생	
	 2) 상태를 가질 수 없다.

	 함수 객체란 무엇일까? -> [함수처럼 동작]하는 객체
	 () 연산자 오버로딩이 필요하다.
	*/
	HelloWorld();

	Functor functor; // 상태값을 가지면서
	functor(); // 일반함수처럼 호출할 수 있다....
	bool ret = functor(3);

	/* MMO에서 함수 객체를 사용하는 예시
	클라 <-> 서버
	서버 : 클라가 보내준 네트워크 패킷을 받아서 처리
	ex) 클라 : 나 (5, 0) 좌표로 이동시켜줘!
	
	요청하는 기능을 바로 실행하는 게 아니라 나열을 해서 들어온 순서대로 하나씩 실행하게 된다.
	-> 보통은 함수는 딱 호출하고 일감을 실행해서 바로 끝나는 형태가 된다.. -> HelloWorld()의 경우
	그러나 함수 객체는 Functor를 만들어주는 시점과 실제 실행하는 시점을 나눠주는 장점이 생긴다.
	*/

	// 예시) 당장 처리할 여력이 안된다하면 기다렸다가 나중에 여유 될 때 일감을 실행한다.
	// task의 일감을 만들어주는 시점
	MoveTask task;
	task._playerId = 100;
	task._posX = 5;
	task._posY = 0;

	// 나중에 여유가 될 때 일감을 실행하는 시점.
	task();

	// -> 이거를 command pattern(커맨드 패턴)


	return 0;
}
