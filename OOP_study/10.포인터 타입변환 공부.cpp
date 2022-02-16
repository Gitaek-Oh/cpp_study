#include <iostream>
using namespace std;

class Knight
{

public:
	int _hp = 0;
};

class Item
{
public:
	Item()
	{
		cout << "Item()" << endl;
	}

	Item(int itemType) : _itemType(itemType)
	{
		cout << "Item(int)" << endl;
	}

	Item(const Item& item)
	{
		cout << "Item(const Item&)" << endl;
	}

	virtual ~Item()
	{

	}
public:
	int _itemType = 0;
	int _itemDbid = 0;

	char _dummy[4096] = {};
};

enum ItemType
{
	IT_WEAPON=1,
	IT_ARMOR,
};

class Weapon : public Item
{

public:
	Weapon() : Item(IT_WEAPON)
	{
		cout << "Weapon()" << endl;
		_damage = rand() % 100;
	}

	~Weapon()
	{
		cout << "~Weapon()" << endl;
	}
public:
	int _damage = 0;
};

class Armor : public Item
{

public:
	Armor() : Item(IT_ARMOR)
	{
		cout << "Armor()" << endl;
	}

	~Armor()
	{
		cout << "~Armor()" << endl;
	}

public:
	int defence = 0;
};

void TestItem(Item item)
{

}
void TestItemPtr(Item* item)
{

}

int main()
{
	/* 복습
	{
		// Stack [ type(4) dbid(4) dummy(4096) ]
		Item item;

		// Stack [ 주소(4~8바이트) ] -> Heap [ type(4) dbid(4) dummy(4096) ]
		Item* item2 = new Item();
		// 함수인자로 넘겨주기 때문에 메모리에 부담을 준다. (생성자와 소멸자가 호출이 된다.)
		TestItem(item);
		TestItem(*item2);

		//포인터나 참조를 넘겨주게 되면 주소 값만 넘겨주기 때문에 생성자와 소멸자는 호출이 되지는 않는다.
		TestItemPtr(&item);
		TestItemPtr(item2);

		// 누락하게 되면 메모리 누수(Memory Leak)가 일어난다. -> 점점 가용 메모리가 줄어들어서 Crash
		delete item2;
	}

	//배열
	{
		cout << "------------------------------------------------------------" << endl;

		// 진짜 아이템이 100개 있는 것 (스택 메모리에 올라와 있다)
		Item item3[100] = {}; // 생성자가 호출이 됨

		cout << "------------------------------------------------------------" << endl;

		// 아이템을 가르키는 바구니가 100개. 실제 아이템은 1개도 없을 수도 있음.
		Item* item4[100] = {}; // 생성자가 호출이 안됨

		//실제 아이템을 만들려면 아래와 같이 만든다
		for (int i = 0; i < 100; i++)
			item4[i] = new Item();
		for (int i = 0; i < 100; i++)
			delete item4[i];

	}
	*/
	// 연관성이 없는 클래스 사이의 포인터 변환 테스트
	// Stack [주소] -> Heap [_hp(4)]
	{
		Knight* knight = new Knight();

		//Item* item = (Item*)knight;
		//item->_itemType = 2;
		//item->_itemDbid = 1;

		delete knight;
	}

	// 자식 -> 부모 변환 테스트
	{
		Weapon* weapon = new Weapon();

		//암시적으로도 된다!, 무기는 아이템이다 -> O
		Item* item = weapon;

		delete weapon;
	}
	
	// 부모 -> 자식 변환 테스트
	{
		Item* item = new Item();

		//Weapon* weapon = (Weapon*)item; // 아이템은 무기이다 -> X
		//weapon->_damage = 10; // Crash가 난다 (이상한 메모리를 건드리기 때문)
		
		delete item;
	}

	// 명시적으로 타입 변환할 때는 항상 조심해야 한다!
	// 암시적으로 될 때는 안전하다?
	// -> 평생 명시적으로 타입 변환(캐스팅)은 안 하면 되는거 아닌가...?
	Item* inventory[20] = {};
	
	srand((unsigned int)time(nullptr));

	for (int i = 0; i < 20; i++)
	{
		int randValue = rand() % 2; //0 ~ 1

		switch (randValue)
		{
		case 0:
			inventory[i] = new Weapon();
			break;
		case 1:
			inventory[i] = new Armor();
			break;
		}
	}

	//인벤토리 목록 출력
	for (int i = 0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;
		
		if (item->_itemType == IT_WEAPON)
		{
			Weapon* weapon = (Weapon*)item;
			cout << "Weapon Damage : " << weapon->_damage << endl; // 데미지가 출력이 잘 된다.
		}
		
	}
	
	// ************************************ 매우 중요한 내용 ************************************
	for (int i = 0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;
		
		//왜 자동으로 소멸자를 불러주지 않는가.....?
		/*if (item->_itemType == IT_WEAPON)
		{
			Weapon* weapon = (Weapon*)item;
			delete weapon;
		}

		else 
		{
			Armor* armor = (Armor*)item;
			delete armor;
		}*/

		// 가상함수를 부모 소멸자에 붙여주면 객체 첫번째 주소 offset에 박히게 되어 자식들의 소멸자가 실행이 된다....?
		
		// 가상함수
		// 부모클래스 생성자()
		// 자식클래스 생성자()
		// ~자식클래스 소멸자()
		// ~부모클래스 소멸자()
		// 가상함수 -> 이런 느낌이라고 해야할까....?
		
		// 이런식으로 실행되기 때문에 자식 클래스의 소멸자가 실행된다고 생각하면 될 것 같다.
		// 따라서 상속관계에서는 무조건 가상함수인 virtual을 붙여줘야 한다!!!!!!!!!!!!
		// 그렇지 않으면 소멸자가 일부만 실행되어서 지워야되는 메모리가 남아있는 경우가 생기게 된다!
		delete item;
	}

	// [결론]
	// - 포인터 vs 일반 타입의 차이를 알아야 한다. (Knight k vs Knight* k)
	// - 포인터 사이의 타입 변환(캐스팅)을 할 때는 매우 매우 조심해야 한다!
	// - 부모, 자식 관계에서 부모 클래스의 소멸자에는 까먹지말고 virtual을 붙이자!!!!!

	return 0;
}
