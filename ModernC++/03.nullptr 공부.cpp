#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

void Test(int a)
{
	cout << "Test(int)" << endl;
}

void Test(void* ptr)
{
	cout << "Test(*)" << endl;
}

class Knight
{
public:
	void TEST()
	{

	}
};

// nullptr 구현
class NullPtr
{
public:
	// 그 어떤 타입의 포인터와도 치환 가능
	template<typename T>
	operator T* () const
	{
		return 0;
	}

	// 그 어떤 타입의 멤버 포인터와도 치환 가능
	template<typename C, typename T> // Class타입 C, template타입 T
	operator T C::* () const
	{
		return 0;
	}

private:
	void operator&() const; // 주소값 &을 막는다
};

const NullPtr _NullPtr; // nullptr과 같다.

Knight* FindKnight()
{
	// TODO

	return nullptr;
}
int main()
{
	// #define NULL 0 으로 정의되어 있다.

	// 1) 오동작
	// 아래 두 개를 호출하면 Test(int a)를 호출하게 된다, 포인터를 활용 못함
	Test(0);
	Test(NULL);
	// nullptr을 사용하면 포인터 함수를 호출하게 된다.
	Test(nullptr);

	// 2) 가독성
	auto knight = FindKnight();
	if (knight == nullptr)
	{

	}

	auto whoami = nullptr; // auto를 통해서 타입이 nullptr_t라는 걸 알 수 있다.

	void (Knight:: * memFunc)();
	memFunc = &Knight::TEST;

	if (knight == _NullPtr)
	{

	}

	//&_NullPtr;  &는 막혀있다.

	return 0;
}