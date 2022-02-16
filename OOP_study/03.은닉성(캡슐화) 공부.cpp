#include <iostream>
using namespace std;

/*
은닉성(Data Hiding) = 캡슐화(Encapsulation)
몰라도 되는 것은 깔끔하게 숨기겠다!
숨기는 이유?
- 정말 위험하고 건드리면 안되는 경우
- 다른 경로로 접근하길 원하는 경우

public: 공개적으로 사용이 가능하다.
protected: 상속받은 자손들만 사용이 가능하다.
private: 클래스 내부에서만 사용이 가능하다.

상속 접근 지정자: 다음 세대한테 부모님의 유산을 어떻게 물려줄지?
public: 공개적인 상속, 부모님의 유산 설계 그대로 물려준다 (public -> public, protected -> protected)
protected: 보호받은 상속, 내 자손들한테만 물려준다 (public -> protected, protected -> protected)
private: 개인적인 상속, 나까지만 잘 쓰고 자손들한테는 안물려준다 (public -> private, protected -> private)
*/
class Car
{
public:
	void MoveHandle() { }
	void PushPedal() { }
	void OpenDoor() { }

	void TurnKey()
	{
		RunEngine();
	}

protected:
	void RunEngine() { }
	void ConnectCircuit() { }

private:
	void DisassembleCar() { }

};

//물려받은걸 자신만 잘 활용하고 더이상 물려주지 않겠다는 의미?
class SuperCar : private Car //상속 접근 지정자
{
public:
	void PushRemoteController()
	{
		RunEngine();
		//DisassembleCar(); // private는 클래스 내부에서만 사용이 가능하기에 오류가 발생
	}
};

class TestSuperCar : private SuperCar
{
	void Test()
	{
		//RunEngine(); // 개인적인 상속으로 더이상 물려받을 수 없기에 오류가 발생한다.
	}
};

class TestSuperCar1 : public SuperCar
{
	void Test()
	{

	}
};


int main()
{
	Car car;
	//car.RunEngine(); //상속받은 자손만 사용이 가능하기에 오류가 발생

	SuperCar car0;
	//car0.MoveHandle(); // MoveHandle 이 개인적인 상속을 받았기 때문에 사용이 불가능하다.

	TestSuperCar1 car1;
	car1.PushRemoteController(); //PushRemoteController 가 공개적인 상속을 받았기 때문에 사용이 가능하다.

	return 0;
}
