#include <iostream>
using namespace std;

class Knight
{
public:
	//기본 생성자 (인자가 없음)
	Knight()
	{
		cout << "Knight() 기본생성자 호출" << endl;

		_hp = 100;
		_attack = 10;
		_posY = 0;
		_posX = 0;
	}

	//기타 생성자, 생성자라 하더라도 인자가 들어가는게 가능(기본은 인자X)
	//인자가 하나만 들어가는 경우는 [타입 변환 생성자]라고 부르기도 한다.
	Knight(int hp)
	{
		_hp = hp;
	}

	//명시적 생성자, 암시적으로 형변환 못하게 막아준다(암시적으로 사용하다가 문제가 발생할 수도 있기 때문이다)
	explicit Knight(int hp)
	{
		_hp = hp;
	}


	//복사 생성자 (자기 자신의 클래스 참조 타입을 인자로 받음)
	Knight(const Knight& knight) //복사해야 되기때문에 const가 들어가야 좋다or한다?
	{
		_hp = knight._hp;
		_attack = knight._attack;
		_posX = knight._posX;
		_posY = knight._posY;

	}

	//소멸자는 1개만 생성가능
	//생성자가 어떻게 만들어졌건 소멸하는 단계에서는 별반차이가 없다.
	~Knight()
	{
		cout << "Knight() 소멸자 호출" << endl;
	}
public:
	void Move(int y, int x);
	void Attack();
	void Die()
	{
		_hp = 0;
		cout << "Die" << endl;
	}

public:
	int _hp = 0;
	int _attack = 0;
	int _posY = 0;
	int _posX = 0;

};
void Knight::Move(int y, int x)
{
	_posY = y;
	_posX = x;
	cout << "Move" << endl;
}

void Knight::Attack()
{
	cout << "Attack" << endl;
}

int main()
{
	//기본 생성자
	Knight k1;
	k1._hp = 100;
	k1._attack = 10;

	//기타 생성자
	Knight k1(30);
	cout << k1._hp << endl; //hp가 30으로 출력됨

	//복사 생성자
	//복사 생성자가 없어도 실행된다 -> 기본생성자가 default로 있어서 문제없다.
	Knight k3(k1);
	Knight k4 = k1; // 이것도 복사생성자 (생성되자마자 복사되는 형태) -> 객체의 복사본을 생성한다.

	//복사 대입 연산자
	// 위에 있는 복사생성자와 방식이 달라진다
	// 기본생성자를 만든 다음 복사 생성자를 실행하기 때문에 주의가 필요하다.
	// 이미 생성되어 있는 객체에 값만 복사할 때 사용된다.
	Knight k5; // 생성자
	k5 = k1; //복사 생성자
	
	// 복사 생성자와 복사 대입 연산자의 차이
	// 복사 생성자는 객체의 복사본을 생성할때 호출되는 생성자이다.
	// 복사 대입 연산자는 객체를 따로 만들고 값만 복사해서 사용하는 연산자이다.

	//암시적 형변환 -> 컴파일러가 알아서 바꿔준다.
	//int num = 1;
	//float f = num;
	//명시적 형변환 -> 내가 num을 float형으로 바꾸라고 주문을 한다.
	//float f = (float)num;

	//타입 변환 생성자를 호출할 수 있다. (기타 생성자)
	//암시적으로 호출될 수 있어서 문제가 발생할 수가 있다.
	//따라서 명시적인 용도로만 사용하게 하려면 앞에 explicit를 붙여서 사용해주면 된다. (위에 만들었다)
	//explicit 생성자로 실행을 하면 오류가 발생한다.
	k5 = 1;

	// 이런식으로 명시적으로 해주면 explicit 생성자가 있어도 실행이 가능하다. (명시적으로 내가 주문했기 때문에?)
	k5 = (Knight)1;

	k1.Move(2, 2);
	k1.Attack();
	k1.Die();

	return 0;
}
