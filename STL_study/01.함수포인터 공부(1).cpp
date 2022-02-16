#include <iostream>
using namespace std;

int Add(int a, int b)
{
	return a + b;
}

class Item
{
public:
	Item()
	{

	}
public:
	int _itemId = 0;	// 아이템 ID
	int _rarity = 0;	// 희귀도
	int _ownerId = 0;	// 소지자 ID
};

typedef bool (ITEM_SELECTOR)(Item*);

Item* FindItem(Item items[], int itemCount, ITEM_SELECTOR* selector/*동작*/)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		// TODO 동작
		if(selector(item))
		return item;

	}

	return nullptr;
}

bool IsRareItem(Item* item)
{
	return item->_rarity >= 2;
}

Item* FindItemByItemId(Item items[], int itemCount, int itemId)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		if (item->_itemId == itemId)
			return item;
	}

	return nullptr;
}

int main()
{
	int a = 10;
	typedef int DATA;

	// int* printer = &a;
	DATA* pointer = &a;

	// 함수
	// int Add(int a, int b);
	typedef int(FUNC_TYPE)(int, int);

	/*1) 포인터			*
	2) 변수이름			fn
	3) 데이터 타입 함수	(인자는 int, int 반환은 int)*/
	FUNC_TYPE* fn;
	
	
	int result = Add(1, 2);	
	/*0010194F  push        2
		00101951  push        1
		00101953  call        Add(010143Dh) 여기서 Add는 주소를 불러온다...
		00101958  add         esp, 8
		0010195B  mov         dword ptr[result], eax
	-> 함수의 이름은 함수의 시작 주소 (배열과 유사)*/

	
	// 함수 포인터
	fn = Add;
	
	int result1 = fn(1, 2); // 기본 문법
	/*00B51965  mov         esi, esp
		00B51967  push        2
		00B51969  push        1
		00B5196B  call        dword ptr[fn]
		00B5196E  add         esp, 8
		00B51971  cmp         esi, esp
		00B51973  call        __RTC_CheckEsp(0B5128Fh)
		00B51978  mov         dword ptr[result1], eax*/

	int result2 = (*fn)(1, 2); // 함수 포인터는 *(접근 연산자) 붙여도 함수 주소를 불러온다!
	/*00B5197B  mov         esi, esp
		00B5197D  push        2
		00B5197F  push        1
		00B51981  call        dword ptr[fn]
		00B51984  add         esp, 8
		00B51987  cmp         esi, esp
		00B51989  call        __RTC_CheckEsp(0B5128Fh)
		00B5198E  mov         dword ptr[result2], eax*/

	Item items[10] = {};
	items[3]._rarity = 2;
	Item* rareItem = FindItem(items, 10, IsRareItem);

}
