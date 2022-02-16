#include <iostream>
using namespace std;

class Pet
{
public:
	Pet()
	{
		cout << "Pet()" << endl;
	}
	~Pet()
	{
		cout << "~Pet()" << endl;
	}
	Pet(const Pet& pet)
	{
		cout << "Pet(const Pet& pet)" << endl;
	}
};

class RabbitPet : public Pet
{

};


class Knight
{
public:
	Knight()
	{
		_pet = new Pet();
	}

	// 깊은 복사를 하려면 복사 생성자(자기 자신의 값을 대입)를 생성
	Knight(const Knight& knight)
	{
		_hp = knight._hp;
		//_pet = knight._pet; -> 얕은 복사가 됨
		_pet = new Pet(*knight._pet); // 깊은 복사 (new -> 새로운 생성자를 만들기 때문에 새로운 주소를 받는다) 
		// Pet(const Pet& pet)은 포인터를 받는게 아니라 객체 자체의 다른 이름을 받기 때문에 knight가 포인터이기 때문에 *을 찍어준다.
	}
	
	// 깊은 복사를 하려면 오퍼레이터도 명시적으로 만들어줘야 한다.
	Knight& operator=(const Knight& knight)
	{
		_hp = knight._hp;
		_pet = new Pet(*knight._pet); // 깊은 복사 
		return *this;
	}
	~Knight()
	{
		delete _pet;
	}
public:
	int _hp = 100;
	// Pet 클래스가 Knight 클래스안에 있으면 Pet의 생성자와 소멸자도 같이 실행되기도 하고 
	// Pet에 4096 byte 짜리 메모리가 있다면 메모리 누수가 생길수도 있고 Pet의 값이 잘못설정되어 크래쉬가 날 수 있기 때문에 
	// Pet만 따로 불러오고만 싶으면 포인터를 넣으면 된다.
	Pet* _pet;
};


int main()
{
	//Pet* pet = new Pet();
	
	Knight knight;
	knight._hp = 200;
	//knight._pet = pet;
	
	Knight knight2 = knight; // 복사 생성자
	//Knight knight3(knight);

	Knight knight3; //기본 생성자
	knight3 = knight; // 복사 대입 연산자

	 /*[복사 생성자] + [복사 대입 연산자]
	 둘 다 안 만들어주면 컴파일러가 '암시적으로' 만들어준다.
	 컴파일러가 알아서 잘 만들어준다?
	 수고하세요 ~ 다음 주제로 넘어갈까요? << no

	 [ 얕은 복사 shallow copy ] 
	 멤버 데이터를 비트열 단위로 '똑같이' 복사 (메모리 영역 값을 그대로 복사)
	 포인터는 주소값을 담는 바구니 -> 동일한 객체를 가리키는 상태가 됨
	 stack : knight1 [ hp, 0x1000(pet) ] -> heap 0x1000에 pet[ ]이 들어있다. 
	 stack : knight2 [ hp, 0x1000(pet) ]
	 stack : knight3 [ hp, 0x1000(pet) ]
	 클래스 안에 heap 영역의 pet 생성자와 소멸자를 만들면 오류가 발생한다. -> knight가 3개 있기 때문에 3번 delete를 시켜줘서 오류가 발생한다. (use-after-free...?)

		 [ 깊은 복사 deep copy ] 
	 멤버 데이터가 참조(주소) 값이라면, 데이터를 새로 만들어준다 (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
	 포인터는 주소값을 담는 바구니 -> 새로운 객체를 생성 -> 상이한 객체를 가리키는 상태가 됨
	 stack : knight1 [ hp, 0x1000(pet) ] -> heap 0x1000에 pet[ ]이 들어있다. 
	 stack : knight2 [ hp, 0x2000(pet) ] -> heap 0x2000에 pet[ ]
	 stack : knight3 [ hp, 0x3000(pet) ] -> heap 0x3000에 pet[ ]

	 결론적으로 암시적으로 만드는 것도 한계가 있다는 것을 알 수 있다.

	 실험)
	 - 암시적 복사 생성자 steps
	 1) 부모 클래스의 복사 생성자 호출
	 2) 멤버 클래스의 복사 생성자 호출
	 3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 shallow copy)
	
	 - 명시적 복사 생성자 steps
	 1) 부모 클래스의 기본 생성자 호출
	 2) 멤버 클래스의 기본 생성자 호출
	
	 - 암시적 복사 대입 연산자 steps
	 1) 부모 클래스의 복사 대입 연산자 호출
	 2) 멤버 클래스의 복사 대입 연산자 호출
	 3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 shallow copy)
	
	 - 명시작 복사 대입 연산자 steps
	 1) 알아서 해주는거 없음

	 왜 이렇게 혼란스러운가?
	 객체를 '복사'한다는 것은 두 객체의 값들을 일치시키려는 것
	 따라서 기본적으로 컴파일러가 해주는 방식은 얕은 복사 (shallow copy) 방식

	 명시적 복사 -> [모든 책임]을 프로그래머한테 위임하겠다는 의미*/
	return 0;
}
