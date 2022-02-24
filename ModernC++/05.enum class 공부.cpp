#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

// unscoped enum (범위없는, 전역으로 나가기 때문에 다른 곳에서 쓸 수가 없다)
enum PlayerType
{
	None,
	PT_KNIGHT, // 1씩 증가
	PT_ARCHER,
	PT_MAGE
};

enum MonsterType
{
	None, // unscoped enum을 사용하게 되면 이름이 겹처서 문제가 된다.
};

enum class ObjectType // 안에 이름자체가 영역안에서 유용하기 때문에
{
	Player,
	Monster,
	Projectile
};

enum class ObjectType2 // 이름을 재활용 할 수 있다.
{
	Player,
	Monster,
	Projectile
};

int main()
{
	// enum class (scoped enum)
	// 1) 이름광간 관리 (scoped)
	// 2) 암죽적인 변환 금지

	double value = static_cast<double>(ObjectType::Player); // 타입이 ObjectType이기 때문에 귀찮지만 캐스팅을 써야한다....

	int choice;
	cin >> choice;

	if (choice == static_cast<int>(ObjectType::Monster))
	{

	}

	unsigned int bitFlag;
	bitFlag = (1 << static_cast<int>(ObjectType::Player));

	// enum은 이름이 겹치면 안되는 단점이 있고 enum class는 캐스팅을 사용해야 한다는 단점이 있는 것 같다...
	// 둘 다 현업에서 쓰니 알아두는 것이 좋을 것 같다.
	return 0;
}