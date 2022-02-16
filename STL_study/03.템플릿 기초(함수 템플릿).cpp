#include <iostream>
using namespace std;

/*
void Print(int a) {cout << a << endl;}
void Print(float a) {cout << a << endl;}
void Print(double a) {cout << a << endl;}
void Print(const char* a) {cout << a << endl;}

Print는 가만히 냅두고 안에 있는 타입만 바꾸고 싶다... (시그니처가 비슷할 때) -> 템플릿 활용 가능
*/
template<typename T>
void Print (T a) { cout << a << endl; }

template<typename T>
int Add(T a, T b) { return a + b; }
// 각기 타입이 다른 경우는 어떻게하면 될까? ex) Print(const char*, int)

template<typename T1, typename T2>
void Print(T1 a, T2 b) { cout << a << " " << b << endl; }

class Knight
{
public:
	// ...

public :
	int _hp = 100;
};

// 연산자 오버로딩 (전역함수 버전) -> cout를 F12로 눌러서 확인이 가능하다.
// __PURE_APPDOMAIN_GLOBAL extern _CRTDATA2_IMPORT ostream cout;
ostream& operator<<(ostream& os, const Knight& k)
{
	os << k._hp;
	return os;
}

// 템플릿 특수화
template<>
void Print(Knight a)
{
	cout << "Knight !!" << endl;
	cout << a._hp << endl;
}
int main()
{
	/* 템플릿 : 함수나 클래스를 찍어내는 틀
	 1) 함수 템플릿 -> 알아보자
	 2) 클래스 템플릿*/
	
	Print<int>(50); // 명시적으로 표현해도 된다...
	Print(50);
	Print(50.0f);
	Print(50.0);
	Print("Hello World");
	
	int result1 = Add(1, 2);
	float result2 = Add<float>(1.1f, 2.2f);

	Print("Hello", 100);

	Knight k1;
	Print(k1);

	return 0;
}
