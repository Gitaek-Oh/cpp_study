#include <iostream>
using namespace std;

struct StatInfo
{
	int hp;
	int attack;
	int defence;
};
// 상속 -> 부모가 자식에게 유산을 물려주는 것
class Player
{
public:
	Player()
	{
		_hp = 0;
		_attack = 0;
		_defence = 0;
		cout << "Player 기본생성자 호출" << endl;
	}

	~Player() //소멸자는 메모리를 정리할 때 유용하기도 하다.
	{
		cout << "Player 소멸자 호출" << endl;
	}
	void Move() { cout << "Player Move 호출" << endl; }
	void Attack() { cout << "Player Attack 호출" << endl; };
	void Die() { cout << "Player Die 호출" << endl; };

public:
	int _hp;
	int _attack;
	int _defence;
};
//상속의 형태로 : 를 사용하여 클래스를 사용한다.
//이렇게 사용하면 Player가 가지고 있는 public 값들이 상속된다.
//Player[  Knight[ ]  ] -> 이런 형태라고 생각하면 된다.
class Knight : public Player
{
public:
	/*
	예외적으로 생성자와 소멸자는 물려주지 않는다. 자기만의 생성자와 소멸자로 생성한다.
	생성자 호출순서는 다음과 같이 나온다.
	Player() 기본생성자 호출 -> 부모
	Knight() 기본생성자 호출 -> 자식
	~Knight() 소멸자 호출 ->자식
	~Player() 소멸자 호출 -> 부모
	*/
	Knight()
		/*
		중괄호와 Knight 사이의 이 구간을 선처리 영역이라고 불리기도 한다.
		이 사이에서 Player(부모)의 생성자를 호출하기 때문이다.
		*/
	{
		_stamina = 0;
		cout << "Knight 기본생성자 호출" << endl;
	}

	~Knight()
	{
		cout << "Knight 소멸자 호출" << endl;
	}
	/*
	후처리 영억으로 ~Player() 소멸자를 호출한다.
	*/

	int _stamina; //상속받은 것 말고도 다른것도 덧붙여서 사용할 수 있음
	void Move() { cout << "Player Die 호출" << endl; }
};

class Mage : public Player
{

};


int main()
{
	Knight k;

	//자식 클래스를 호출하고 사용하면 부모 클래스에 있는 값들을 사용할 수 있다.
	k._hp = 100;
	k._attack = 10;
	k._defence = 5;
	k._stamina = 100; //상속받은 것 말고도 자식 클래스에 변수를 추가해서 사용할 수 있다.

	k.Attack();
	k.Die();
	k.Move(); // 상속받은 것을 자식클래스에서 수정해서 사용할 수 있다.
	k.Player::Move(); // 상속받은 것을 다시 사용할 수 있다. (자식클래스에서 다시 정의했다 하더라도 완전히 없어지는 것은 아니다.)

	return 0;
}

// 상속성은 결론적으로 공통적인 부분을 쉽게 관리할 수 있다고 생각한다.
// 부모 [  자식[ ], 자식[ ]  ] 이런식으로 생각하면 쉬울것 같다.
// 자식은 부모에게 상속받은 것을 쓸 수도 있고 안쓸 수도 있다.
