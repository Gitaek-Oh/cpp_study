#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

class Knight
{
public:
	Knight() { cout << "기본 생성자" << endl; }
	Knight(const Knight&) { cout << "복사 생성자" << endl; }
	Knight(Knight&&) noexcept { cout << "이동 생성자" << endl; }
};

void Test_Copy(Knight k)
{

}

template<typename T>
void Test_ForwardingRef(T&& param) // 전달 참조
{
	// 왼 값을 넣어줬으면 왼값 참조!
	// 오른 값을 넣어줬으면 오른값 참조!
	//Test_Copy(param); 인자를 오른값으로 받아줬어도 param 자체는 왼값이기 때문에 Test_Copy는 왼값으로 받아준다! (복사생성자가 실행됨)

	//TODO
	// 왼값 참조라면 복사
	// 오른값 참조라면 이동
	Test_Copy(std::forward<T>(param));

}
void Test_RValueRef(Knight&& k) //오른값 참조
{

}

int main()
{
	// 전달 참조 (forwarding reference) C++17

	// && &를 두번쓰면 오른값 참조
	Knight k1;

	Test_RValueRef(std::move(k1)); //rvalue_cast
	Test_ForwardingRef(std::move(k1)); // rvalue_cast
	Test_ForwardingRef(k1); // lvalue_cast로 들어간다?

	auto&& k2 = k1; // lvalue_cast로 들어간다?
	auto&& k3 = std::move(k1); // rvalue_cast

	// 공통점 : 형식 연역 (type deducation)이 일어날 때
	// 전달 참조는 왼값을 넣어주면 왼값참조가 되고 오른값을 넣어주면 오른값참조가 된다! (&&가 무조건 오른값 참조가 아니다!)
	// 왼값, 오른값을 둘 다 만들려면 함수를 두개씩 만들어줘야 했기 때문에 (인자가 2개가 되면 4개를 만들어야 된다;;) 전달 참조를 만들어 줬다!

	Knight& k4 = k1; // 왼값 참조
	Knight&& k5 = std::move(k1); // 오른값 참조

	// 오른값 : 왼값이 아니다 = 단일식에서 벗어나면 사용 X
	// 오른값 참조 : 오른값만 참조할 수 있는 참조 타입
	//Test_RValueRef(k5); k5가 오른값 참조를 받았어도 얼마든지 왼값으로 변할수 있기 때문에 std::move를 붙여줘야한다!! k5자체는 오른값이 아니다!
	Test_RValueRef(std::move(k5));
	return 0;
}