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
	Knight()
	{

	}

	Knight(initializer_list<int> li)
	{
		cout << "Knight(initializer_list) 호출" << endl;
	}

	Knight(int a, int b)
	{
		cout << "Knight(int, int) 호출" << endl;
	}
};
int main()
{
	// 중괄호 초기화 { }
	int a = 0;
	int b(0);
	int c{ 0 };

	Knight k1;
	Knight k2 = k1; // 복사 생성자

	Knight k3{ k1 };

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2(10, 1); // size = 10, data = 1 초기값

	int arr[] = { 1,2,3,4 };



	// 중괄호 초기화
	// 1) vector 등 container와 잘 어울린다.
	vector<int> v3{ 1,2,3,4 }; // 1,2,3,4를 push_back한 것과 같다.

	// 2) 축소 변환 방지
	int x = 0;
	double y{ x }; // 축소 변환이 필요하다고 에러가 발생한다.

	// 3) Bonus
	Knight k4(); // 이 함수는 기본생성자가 아니기 때문에 에러가 발생한다. 기본생성자는 Knight k4;
	Knight k4{ }; // 중괄호를 넣으면 기본생성자를 호출한다.

	// 중괄호 초기화의 단점 (initializer_list, 최상위 포식자!!)
	Knight k5{ 1,2,3,4 }; // 이런식으로 사용하려면 initializer_list를 사용해야한다!
	Knight k5{ 1,2 }; // 이 함수는 (int,int)를 불러오는게 아니라 initializer_list를 불러오게 된다.
	vector<int> v4{ 1,2 }; // 이 함수는 (size, data)를 불러오는게 아니라 initializer_list 불러오게 된다.

	// 괄호 초기화 ()를 기본으로 간다
	// - 전통적인 c++ (거부감이 없음)
	// - vector 등 특이한 케이스에 대해서만 { } 사용

	// 중괄호 초기화 { } 를 기본으로 간다
	// - 초기화 문법의 일치화
	// - 축소 변환 방지
	return 0;
}