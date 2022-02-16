#include <iostream>
using namespace std;

 /*typename T를 붙이면 '조커카드' (어떤 타입도 다 넣을 수 있음)
 그런데 무조건 typename을 붙여야 하는 것은 아니다.....
 template< > 안에 들어가는 건 (골라줘야 하는 목록)이라 볼 수 있음*/
template<typename T, int SIZE>
class RandomBox
{
public:
	T GetRandomData()
	{
		int idx = rand() % SIZE;
		return _data[idx];
	}
public:
	T _data[SIZE];
};

// 템플릿 특수화
// 특정 매개변수에 대해서는 별도처리를 하고 싶은 경우 특수화를 이용한다.
template< int SIZE>
class RandomBox<double, SIZE>
{
public:
	double GetRandomData()
	{
		cout << "RandmonBox(double)" << endl;
		int idx = rand() % SIZE;
		return _data[idx];
	}
public:
	double _data[SIZE];
};

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	/* 템플릿 : 함수나 클래스를 찍어내는 틀
	 1) 함수 템플릿 
	 2) 클래스 템플릿 -> 알아보자*/

	RandomBox<int, 10> rb1;

	for (int i = 0; i < 10; i++)
	{
		rb1._data[i] = i;
	}
	int value1 = rb1.GetRandomData();
	cout << value1 << endl;

	RandomBox<float, 20> rb2;

	for (int i = 0; i < 20; i++)
	{
		rb2._data[i] = i + 0.5f;
	}
	float value2 = rb2.GetRandomData();
	cout << value2 << endl;

	RandomBox<double, 20> rb3;
	for (int i = 0; i < 20; i++)
	{
		rb3._data[i] = i + 0.5;
	}
	double value3 = rb3.GetRandomData();
	cout << value3 << endl;

	/*rb1 = rb2;
	 두 타입이 일치하지 않아서 대입이 안된다고 나온다
	 성립이 되려면 둘 다 randombox<int, 10> 이거나 randombox<int, 20> 이어야한다.*/
}
