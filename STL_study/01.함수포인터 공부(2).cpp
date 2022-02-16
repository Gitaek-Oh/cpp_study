#include <iostream>
using namespace std;

class Knight
{
public:
	int GetHp(int, int)
	{
		cout << "GetHp()" << endl;
		return _hp;
	}
public:
	int _hp = 100;

};

/*	typedef의 진실
	typedef 왼쪽 오른값 -> 오른쪽 (커스텀 타입 정의)
	정확히는 왼쪽/오른쪽 기준이 아니라,
	[선언 문법]에서 typedef을 앞에다 붙이는 쪽*/
typedef int INTEGER;
typedef int* POINTER;
typedef int FUNC(int, int);
typedef int ARRAY[20];

typedef int(*PFUNC)(int, int); // 함수 포인터
typedef int(Knight::* PMEMFUNC)(int, int); // 멤버 함수 포인터





int Test(int a, int b)
{
		cout << "TEST" << endl;
		return a + b;
}


int main()
{
	/*함수 포인터
		1) 포인터		*
		2) 변수이름		fn
		3) 타입			함수(인자로 int 2개를 받고,int 1개를 반환)*/

	//int (*fn)(int, int);
	/*위의 내용처럼 한번에 하는 것을 많이 사용한다.
	typedef int(FUNC_TYPE)(int, int);
	FUNC_TYPE* fn;*/
	
	PFUNC fn;

	fn = &Test; // & 생략 가능 (C언어와의 호환성 때문이다, 붙여주는 것을 추천한다.)

	fn(1, 2);
	(*fn)(1, 2);


	// 위 문법으로 만든 함수는 [전역함수/ 정적함수(static)]만 담을 수 있다 (호출 규약이 동일한 애들)
	// fn = &Knight::GetHp; -> 오류 

	// 그냥 호출하는 개념
	Test(1, 2); 

	// 특정 객체를 기반으로 호출하는 개념, k1의 주소도 불러줘야 한다.
	Knight k1;
	k1.GetHp(1,1); 

	// 멤버 함수는 &표시를 반드시 붙여줘야한다.
	PMEMFUNC mfn;
	mfn = &Knight::GetHp;
	//mfn()으로 사용할 수가 없다 -> 객체를 불러줘야하기 때문이다.
	(k1.*mfn)(1, 1);

	Knight* k2 = new Knight();
	// * . 은 -> 대체 가능
	((*k2).*mfn)(1, 1);
	(k2->*mfn)(1, 1);

	delete k2;
	return 0;
}
