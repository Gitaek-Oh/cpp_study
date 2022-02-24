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

public:
	int _hp;
};

template<typename T>
void Print(T t)
{
	cout << t << endl;
}

int main()
{
	/*int a = 3;
	float b = 3.14f;
	double c = 1.23;
	Knight d = Knight();
	const char* e = "test";*/

	auto a = 3;
	auto b = 3.14f;
	auto c = 1.23;
	auto d = Knight();
	auto e = "test";

	/* auto는 일종의 조커카드 , 조커카드?? -> template<typename t> ?
	- 형식 연역 (type deduction)
	-> 말이 되게 잘 맞춰봐~ (추론)
	추론 규칙은 생각보다 복잡해질 수 있다.

	주의!
	기본 auto는 const, & 무시!!!!!!!!!!!!!!!!!*/
	int& reference = a;
	const int cst = a;

	auto test1 = reference; // test1 은 int의 형식
	auto test2 = cst; // test2 는 int의 형식

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		int& data = v[i]; // auto& data = v[i]로 사용해야한다. (어느정도 힌트를 줘야함)
		/*auto data = v[i]; 이런식으로 사용하면 int로 받아주기 때문에 v[i]에 있는 참조 값을 복사하게 된다.
		data = 100으로 임시값을 수정해서 아무런 의미 없는 일을 수행하게 된다.*/
		data = 100;
	}

	/* 아무튼 이제 기존의 타입은 잊어버리고 auto만 사용할래요~~
	-> 타이핑이 너무 길어지는 경우는 OK!
	-> 가독성을 위해 일반적으로는 놔두는게 좋다.*/

	// 타이핑이 길어지는 경우는 다음과 같이 사용하면 된다!
	map<int, int> m;
	auto ok = m.insert(make_pair(1, 100));

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}