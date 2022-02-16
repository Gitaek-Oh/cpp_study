#include <iostream>
using namespace std;

//static 변수, static 함수 (static = 정적 = 고정된)

class Marine
{
public:
	// 특정 마린 객체에 종속적
	int _hp;

	void TakeDamage(int damage)
	{
		_hp -= damage;
	}

	static void SetAttack()
	{
		s_attack = 100;
	}
	//특정 마린 객체와 무관
	// 마린이라는 클래스 자체와 연관
	static int s_attack; //설계도상으로만 존재 (전역함수와 비슷하다)
};

// static 변수는 어떤 메모리?
// 초기화 하면 .data
// 초기화 안 하면 .bss
int Marine::s_attack = 0; //마린을 100마리를 만들더라도 이 메모리를 공용으로 사용하게 된다.

class Player
{
public:
	int _id;
};
int Generateld()
{
	// 생명주기: 프로그램 시작/종료 (메모리에 항상 올라가 있음)
	// 가시범위:

	//정적 지역 객체 (.data 영역이 올라감)
	static int s_id = 1; //int id = 1로 초기화하면 계속 1로 들어가겠지만 static을 사용하면 고정이기 때문에 있던 값을 계속 사용한다.

	return s_id++;
}

int main()
{
	Marine m1;
	Marine m2;
	m1._hp = 35;
	m2._hp = 40;
	Marine::s_attack = 6;
	m1.TakeDamage(10);
	m2.TakeDamage(5);
	//m1.s_attack = 6;
	//m2.s_attack = 6;

	// 마린 공격력 업그레이드 완료!
	Marine::s_attack = 7;
	Marine::SetAttack();// 이것으로 대신할 수 있다.
	//m1.s_attack = 7;
	//m2.s_attack = 7;

	// 함수내부에 static을 만들더라고 해도 스택에 올라가는게 아니라 .data 영역에 들어감 (스택 아님)
	static int id = 10;

	cout << Generateld() << endl; // 1
	cout << Generateld() << endl; // 2
	cout << Generateld() << endl; // 3
	cout << Generateld() << endl; // 4
	cout << Generateld() << endl; // 5

	return 0;
}
