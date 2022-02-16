#include <iostream>
using namespace std;

/*
 다형성(Polymorphism = Poly + morph) = 겉은 똑같은 데,  기능이 다르게 동작한다.
 - 오버로딩(Overloading) = 함수 중복 정의 = 함수 이름의 재사용
 - 오버라이딩(Overriding) = 재정의 = 부모 클래스의 함수를 자식 클래스에서 재정의


바인딩(Binding) = 묶는다
 - 정적 바인딩(Static Binding): 컴파일 시점에 결정
 - 동적 바인딩(Dynamic Binding): 실행 시점에 결정
 일반함수는 정적 바인딩을 사용
 동적 바인딩을 원한다면? -> 가상 함수 (virtual function)

그런데 실제 객체가 어떤 타입인지 어떻게 알고 알아서 가상함수를 호출해준걸까?
 - 가상 함수 테이블 (vftable)
 .vftable [] 4바이트(32비트) 8바이트(64비트) -> 이것도 일종의 주소이다.
 vftable의 주소가 [VMove](첫 번째) [VDie](두 번째)를 가르키고 있었는 데 해당 객체가 원본이 Player 였는지 Knight였는지에 따라가지고 vftable의 값이 달라지게 된다.
 결론은 Player* player 코드 자체만 보면 알 수 없지만 이 객체의 첫 메모리에 내가 호출해야되는 함수의 표지판을 들고있는 셈이다.
 똑같은 Player라고 하더라도 원본이 Knight였는지, Mage였는지에 따라서 알아서 찾아간다.

 디스어셈블리 까보면 다음과 같다.
player->VMove();
01002658  mov         eax,dword ptr [player] -> player의 포인터 값을 eax에 넣어준다. (player의 객체가 저장된 주소)
0100265B  mov         edx,dword ptr [eax] -> eax의 주소를 타고가서 첫번째 값을 edx에 꺼내온다.
~
01002662  mov         eax,dword ptr [edx] -> edx의 값을 eax에 넣어준다
01002664  call        eax -> eax값을 call을 해준다
~
player->VDie();
0100266D  mov         eax,dword ptr [player]
01002670  mov         edx,dword ptr [eax]
~
01002677  mov         eax,dword ptr [edx+4] //+4 offset을 더한 애를 콜한다
0100267A  call        eax
~
*/

//순수 가상 함수 : 구현은 없고 '인터페이스'만 전달하는 용도로 사용하고 싶을 경우
//추상클래스 : 순수 가상 함수가 1개 이상 포함되면 바로 추상 클래스로 간주한다.
//-직접적으로 객체를 만들 수 없게 됨


class Player
{
public:
	Player()
	{
		_hp = 100;
	}
	// 오버로딩으로 함수의 이름은 같은데 들어가는 변수가 다르다.
	void Move() { cout << "Move Player !" << endl; }
	//void Move(int a) { cout << "Move Player (int) !" << endl; }

	//가상 함수 (동적 바인딩)
	virtual void VMove() { cout << "Move Player !" << endl; }
	virtual void VDie() { cout << "Player Die !" << endl; }
	//순수 가상 함수
	virtual void Attack() = 0;

public:
	int _hp;
};

class Knight : public Player
{
public:
	Knight()
		/*
		선처리 영역
		0x007BFB68  00b89b34  4??. -> player의 vftable
		0x007BFB6C  00000064  d...  -> _hp = 100으로 세팅된 부분
		00B81FC8  mov         dword ptr [eax],offset Knight::`vftable' (0B89B5Ch)
		*/
	{
		/*
		0x007BFB68  00b89b5c  \??. ->객체가 이동되어야하는 함수로 세팅된다
		0x007BFB6C  00000064  d...

		00b89b5c의 주소(0x00b89b5c)로 이동하면
		0x00B89B5C  00b81055  U.?. ->Knight의 Move함수
		0x00B89B60  00b81488  ?.?.  ->Knight Die 함수
		*/
		_stamina = 100;
	}
	void Move() { cout << "Move Knight !" << endl; } //오버라이딩으로 부모 클래스의 함수를 자식 클래스에서 재정의 했다.

	//가상 함수는 재정의를 하더라도 가상 함수다!
	void VMove() { cout << "Move Knight !" << endl; }
	virtual void VDie() { cout << "Player Die !" << endl; }
	virtual void Attack() { cout << "Attack Knight !" << endl; }

public:
	int _stamina;
};

class Mage : public Player
{

public:
	int _mana;
};

void MovePlayer(Player* player)
{
	player->Move();
}

void MoveKnight(Knight* knight)
{
	knight->Move();
}

//메모리 주소는 Knight[ Player[ ] ]
void MovePlayer1(Player* player)
{
	/*
	가상함수가 어려워서 이 방식으로 사용할 경우 원본의 메모리를 침범하기 때문에 가상함수를 사용해야 된다.
	Knight* k = (Knight*)player;
	k->_stamina = 100;
	*/
	//가상함수를 사용
	player->VMove();
	player->VDie();
}

int main()
{
	/*
	Player p;
	MovePlayer(&p); // Move Player !

	Knight k;
	MoveKnight(&k); //Move Knight !

	Player p1;
	MovePlayer(&p1); //플레이어는 플레이어다? YES
	//MoveKnight(&p1);
	//플레이어는 기사다? NO -> 자식클래스에서 부모클래스로 넘어가는 건 되지만 부모클래스에서 자식클래스로 넘어가는 건 안된다.
	//플레이어가 기사인지 마법사인지 모른다

	Knight k1;
	MoveKnight(&k1); //기사는 기사다? YES
	MovePlayer(&k1); //기사는 플레이어다? YES (자식클래스 -> 부모클래스로 넘어가는 건 가능)
	*/

	//Knight k;
	//오버라이딩을(재정의)해서 Knight 만의 특수한 이동코드를 만들었지만 정작 Player의 최상위 클래스 하나로 관리하다보니 Player의 Move함수를 호출하게 된다. (정적바인딩)
	//MovePlayer(&k); //Move Player !

	//순수 가상 함수를 가지고 있는 추상클래스이기 때문에 독단적으로 사용할 수 없게 된다. (오류 발생)
	Player p;

	//가상함수 출력 확인 (순수 가상 함수를 넘겨주는 방식으로는 사용할 수 있음 (오류 발생 X))
	Knight k;
	MovePlayer1(&k); //Move Knight !




	return 0;
}
