#include <iostream>
using namespace std;

/*
	캐스팅 (타입 변환)
	(int)~와 같이 타입변환은 c언어이기 때문에 c++언어를 사용해주는 게 좋다?
	1) static_cast
	2) dynamic_cast
	3) const_cast
	4) reinterpret_cast
	
*/

void PrintName(char* str)
{
	cout << str << endl;
}
class Player
{
public:
	virtual ~Player() {};
};

class Knight : public Player
{

};

class Archer : public Player
{

};

class Dog
{

};
int main()
{
	/*	static_cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용해준다.
		1) int <-> float
		2) Player*(부모) -> Knight* (다운 캐스팅)
	*/
	int hp = 100;
	int maxHp = 200;
	float ratio = static_cast<float>(hp) / maxHp; 

	Player* p = new Knight();
	Knight* k1 = static_cast<Knight*>(p); //위험해서 오류가 생김 -> static_cast를 사용해서 타입변환해준다. 단, 안정성은 보장은 못한다.

	/*	dynamic_cast : 상속 관계에서의 안전 형변환
		RTTI (RunTime Type Information) -> virtual 함수(가상함수)
		다형성을 활용하는 방식
		- virtual 함수를 하나라도 만들면, 객체의 메모리에 가상 함수 테이블(vftable) 주소가 기입된다.
		- 만약 잘못된 타입으로 캐스팅을 했으면, nullptr 반환 *********** 중요
		---> Player* p = new Archor();로 설정 후 타입 변환(Knight* k1 = static_cast<Knight*>(p))을 해주면 Archor의 값이 들어가서 메모리가 오염이 되서 문제가 된다.
		---> 가상함수로 해주면 원본 자체가 Knight가 아닐경우 nullptr로 걸러준다. , 원본이 누구인지 모를 때 사용하기도 한다.
		이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인하는데 유용하다.
	*/

	Knight* k2 = dynamic_cast<Knight*>(p);

	//const_cast : const를 붙이거나 떼거나~
	
	PrintName(const_cast<char*>("Test")); // const char 포인터이다 보니까 const를 때서 넘겨줘야한다.

	/*	reinterpret_cast
		가장 위험하고 강력한 형태의 캐스팅
		're-interpret' : 다시-간주하다/생각하다
		- 포인터랑 전혀 관계없는 다른 타입 변환 등
	*/
	
	//__int64 address = k2; //기본적으로는 주소값을 의미하는 k2랑 숫자를 의미하는 _int64랑 관계없기 때문에 오류가 발생
	__int64 address = reinterpret_cast<__int64>(k2);
	
	//말도 안되는 변환도 가능하다.
	Dog* dog1 = reinterpret_cast<Dog*>(k2);

	void* p = malloc(1000);
	Dog* dog2 = reinterpret_cast<Dog*>(p); // c언어에서 쓰던 (Dog*)p;의 캐스팅을 쓰면 위에 있는 캐스팅을 모두 커버하기 때문에 실수할 수 있다.

	return 0;
}
