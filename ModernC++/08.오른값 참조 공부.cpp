#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>


class Pet
{

};
class Knight
{
public:
	Knight()
	{
		cout << "Knight()" << endl;
	}

	// 복사 생성자!
	Knight(const Knight& knight)
	{
		cout << "const Knight()" << endl;
	}

	// 이동 생성자!, 오른값 참조를 사용하려면 생성자 등등 같이 만들어 줘야한다!
	Knight(Knight&& knight)
	{

	}

	~Knight()
	{
		if (_pet)
			delete _pet;
	}

	// 복사 대입 연산자
	void operator=(const Knight& knight)
	{
		cout << "operator=(const Knigjt&)" << endl;

		_hp = knight._hp;
		if (knight._pet) // 다른 기사가 같은 펫을 사용할 수 없기 때문에 new를 사용해준다!
			_pet = new Pet(*knight._pet);
	}

	// 이동 대입 연산자
	void operator=(Knight&& knight)
	{
		cout << "operator=(const Knight&&)" << endl;

		// 얕은 복사
		_hp = knight._hp;
		_pet = knight._pet;

		// 더 이상 원본데이터를 사용하지 않겠다는 이동 대입 연산자이기 때문에 상대방의 펫을 가져올 수 있다?
		_pet = knight._pet;
	}

public:
	int _hp = 100;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight) { }
void TestKnight_LValueRef(Knight& knight) { }
void TestKnight_ConstLValueRef(const Knight& knight) { }
void TestKnight_RValueRef(Knight&& knight) { knight._hp = 100; } // 오른값 참조, 원본의 _hp를 수정해주더라도 문제가 되지 않는다!

int main()
{
	// 오른값(rvalue) 참조와 std::move
	// 왼값(lvalue) vs 오른값(rvalue)
	// lvalue : 단일식을 넘어서 계속 지속되는 개체
	// rvalue : lvalue가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등)

	Knight k1;

	TestKnight_Copy(k1); // 복사가 되지만 k1의 불안전한 복사가 된다.

	TestKnight_LValueRef(k1); // 복사가 일어나지는 않고 주소값을 넘겨주기 때문에 불필요한 복사가 일어나지 않는다!
	//TestKnight_LValueRef(Knight()); const lvalue 오류가 발생함
	// 그러면 왜 const오류가 발생할 까?
	// Knight()는 임시객체라 곧 있으면 사라질 건데 객체안에 값을 고치는 것 자체가 헛짓이기 때문에 문법적으로 const만 오른값을 받아준다!

	TestKnight_ConstLValueRef(Knight());
	// const는 쓰면 고치지 않고 잠시 사용할 용도처럼 보이기 때문에 문법적으로 허용이 된다!
	// 또한 Knight 안에 또 다른 함수를 만들더라도 무조건 const를 붙여줘야한다.

	//TestKnight_RValueRef(k1);  이러면 오른값에 왼값을 넣어주기 때문에 오류가 발생한다.

	TestKnight_RValueRef(Knight());

	// 그런데 오른값 함수에 임시객체(Knight())를 넣어줬는데 왜 문제가 안될까????
	// -> 오른값 함수에는 꼭 임시객체만 넣어줄 수 있는 건 또 아니다!
	TestKnight_RValueRef(static_cast<Knight&&>(k1)); // k1은 실질적으로 존재하는 값이다! 원본도 수정이 가능!

	// void TestKnight_LValueRef(Knight& knight) { }는 knight의 원본은 마음대로 갖고 놀아도 돼!
	// void TestKnight_RValueRef(Knight && knight) { knight._hp = 100; }는 knight의 원본을 사용하지 않을 테니 마음대로 수정해도 돼!
	//  -> 이동 대상! (원본 데이터를 유지하지 않아도 된다!!!) -> 이것의 장점은 뭘까?

	Knight k2;
	k2._pet = new Pet();
	k2._hp = 1000;

	// 원본은 날려도 된다 << 는 Hint를 주는 쪽에 가깝다!
	Knight k3;
	k3 = static_cast<Knight&&>(k2); // 이렇게 사용하면 k3는 k2가 가지고 있는 데이터를 뺏어온다! (복사의 개념이 아님)
	k3 = std::move(k2); // 오른값 참조로 캐스팅, std::move의 본래 이름 후보 중 하나가 rvalue_cast

	// 원래는 별로 사용할 일이 없지만 코어 라이브러리에는 사용하는 일이 있다, 원래는 복사복사해서 사용했지만 이동할 수 있는 것이 생겨서 속도적으로 빨라졌다!

	std::unique_ptr<Knight> uptr = std::make_unique<Knight>(); // 포인터지만 딱 하나만 존재해야하는 함수!
	//std::unique_ptr<Knight> uptr2 = uptr; // 똑같이 uptr값을 만들어주면 오류가 발생한다!
	std::unique_ptr<Knight> uptr2 = std::move(uptr); // 이런식으로 사용할 수도 있다!! (원본 데이터가 uptr2한테 이전되기 때문이다)


	return 0;
}