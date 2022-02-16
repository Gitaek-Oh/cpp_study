#include <iostream>
using namespace std;

// 연산자 오버로딩?
// 일단 [연산자 함수]를 정의해야함
// 함수도 멤버함수 vs 전역함수가 존재하는것처럼, 연산자 함수도 두가지 방식으로 만들 수 있음

// - 멤버 연산자 함수 버전
// -- ap op b 형태에서 왼쪽으로 기준으로 실행됨 (a가 클래스여야 가능, a를 '기준 피연산자'라고 함, op는 오퍼레이션)
// -- 한계) a가 클래스가 아니면 사용 못함

// - 전역 연산자 함수 버전
// -- a op b 형태라면 a,b 모두를 연산자 함수의 피연산자로 만들어준다.

// 그럼 무엇이 더 좋은가? 그런거 없음, 심지어 둘 중 하나만 지원하는 경우도 있기 때문.
// - 대표적으로 대입 연산자 (a=b)는 전역 연산자 버전으로는 못 만든다.

// 복사 대입 연산자
// - 용어가 좀 헷갈린다 [복사 생성자] [대입 연산자] [복사 대입 연산자]
// --복사 대입 연산자 = 대입 연산자 중, 자기 자신의 참조 타입을 인자로 받는 것

// 기타
// - 모든 연산자를 다 오버로딩 할 수 있는 것은 아니다(:: . . 이런건 안됨)
// - 모든 연산자가 다 2개 항이 있는 것은 아님. ++ -- 가 대표적 (단항 연산자)
// - 증감연산자 ++ --
// -- 전위형 (++a) operator++()
// -- 후위형 (a++) operator++(int)

class Position
{
public:
	Position operator+(const Position& arg)
	{
		Position pos;
		pos._x = _x + arg._x;
		pos._y = _y + arg._y;
		return pos;
	}

	bool operator==(const Position& arg)
	{
		return _x == arg._x && _y == arg._y;
	}

	//void operator=(int arg)
	//{
	// _x = arg;
	// _y = arg;
	//}

	//자기 자신의 참조 값
	Position& operator=(int arg)
	{
		_x = arg;
		_y = arg;

		return *this; //내 자신의 주소값을 반환
	}

	//복사 대입 연산자
	//복사 생성자, 복사 대입 연산자 등 특별 대우를 받는 이유는 말 그대로 객체가 '복사'되길 원하는 특징 때문
	Position& operator=(const Position& arg)
	{
		_x = arg._x;
		_y = arg._x;

		return *this; //내 자신의 주소값을 반환
	}


	Position& operator++()
	{
		_x++;
		_y++;

		return *this;
	}

	Position& operator++(int)
	{
		_x++;
		_y++;

		return *this;
	}

	//void operator++(int) //int는 쓰기 위함이 아니라 구별하기 위함이라 뭘 넣을 필요가 없다
	//{
	// _x++;
	// _y++;
	//}
public:
	int _x;
	int _y;

};

// - 전역 연산자 함수 버전
Position operator+(int a, const Position& b)
{
	Position ret;

	ret._x = b._x + a;
	ret._y = b._y + a;

	return ret;
}


int main()
{
	Position pos1;
	pos1._x = 0;
	pos1._y = 0;

	Position pos2;
	pos2._x = 0;
	pos2._y = 0;

	Position pos3 = pos1 + pos2;
	pos3 = pos1.operator+(pos2);

	//pos3 = 1 + pos1; //pos가 왼쪽을 기준으로 실행되야 하기에 오류가 발생하는 단점이 있다.(pos3 = pos1 + 1 이 되어야 오류가 발생안함) -> 멤버 연산자 함수 버전

	Position pos4 = 1 + pos3; //전역 연산자 함수 버전은 오류가 발생안한다.

	bool isSame = (pos3 == pos4);

	//Position pos5 = 5;// 이것은 대입의 느낌이아니라 생성되자마자 5라고 초기화하는 느낌이다. 5라는 숫자를 받는 생성자를 찾게 될 것이다.

	// - 전역 연산자 함수 버전
	Position pos5;
	pos5 = 5;

	pos3 = (pos5 = 5); //pos=5는 void를 리턴하다 보니까 넣을 수가 pos3에 없음 (자기 자신의 참조값을 뱉어줄수 있음)

	++(++pos5);
	(pos5++)++;

	pos5 = pos3++; // const를 붙이게 되면 pos의 복사 값을 넣을 수 있게 된다. (위에 op 참조)

	return 0;
}
