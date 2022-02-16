#include <iostream>
using namespace std;

class Item
{
public:

public:
	int _itemId = 0;
	int _rarity = 0;
	int _ownerId = 0;
};

class FindByOwnerId
{
public:
	bool operator() (const Item* item)
	{
		return (item->_ownerId == _ownerId); // 같으면 true, 아니면 false
	}
public:
	int _ownerId;
};

class FindByRarity
{
public:
	bool operator() (const Item* item)
	{
		return (item->_rarity >= _rarity); // 같으면 true, 아니면 false
	}
public:
	int _rarity;
};

template<typename T>
Item* FindItem(Item items[], int itemCount, T selector)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		// TODO : 조건 체크
		if (selector(item))
			return item;
	}

	return nullptr;
}

int main()
{
	/* 콜백(callback) 함수
		게임을 만들 때 이런 콜백의 개념이 자주 등장한다.
		ex) MoveTask 실습(객체 함수 실습) 등

		어떤 상황이 일어나면 -> 이 기능을 호출해줘
		ex) UI 스킬 버튼을 누르면 -> 스킬을 쓰는 함수를 호출
	*/

	Item items[10];
	items[3]._ownerId = 100;
	items[8]._rarity = 2;

	FindByOwnerId functor1;
	functor1._ownerId = 100;

	FindByRarity functor2;
	functor2._rarity = 1;

	Item* item1 = FindItem(items, 10, functor1);
	Item* item2 = FindItem(items, 10, functor2);
	return 0;
}
