#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

typedef vector<int>::iterator it;

typedef __int64 id;
using id2 = int;

// 1) 직관성
typedef void (*MyFunc)(); // MyFunc 함수를 지칭하는게 아니라 함수 포인터를 지칭하는 건데 보기가 어려움
using MyFunc2 = void(*)(); // 가독성이 매우 좋다!

// 2) 템플릿
template<typename T>
// typedef std::list<T> List2 템플릿과 타입def는 같이 쓸 수 없기 때문에 using을 쓰면 가능하다.
// c++11 이전에는 struct List2를 만들어서 사용했다....
using List = std::list<T> // 템플릿을 다양한 형태로 맞춰주는 것이 가능하다!

// typedef은 using보다 좋지는 않다.... 하지만 아직 쓰는 곳이 있으니 알아는 둬야한다!

int main()
{
	List<int> li;
	li.push_back(0);
	li.push_back(1);
	li.push_back(2);

	return 0;
}