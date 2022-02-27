#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

class Player
{
public:
	virtual void Attack()
	{
		cout << "Player!" << endl;
	}
};

class Knight : public Player
{
public:
	// 재정의(override)
	// 오버로딩(over loading) : 함수 이름의 재사용
	void Attack() override // override를 써주면 부모에게 가져와서 쓰는 것이라고 말해주는 거랑 같고 안전성이 높아지며 가독성도 좋아진다.
	{
		cout << "Knight!" << endl;
	}

	void Attack() final // final을 쓰면 자손들에게 더 이상 오버라이드를 하게 만들어주지 않겠다는 의미이다!
	{
		cout << "Knight!" << endl;
	}
};

int main()
{
	// override, final
	Player* player = new Knight();

	player->Attack(); // 부모 클래스에 virtual를 사용하면 Knight에 있는 Attack도 가상함수로 들어가기 때문에 재정의가 되어 "Knigh!"가 나온다!
	// 그런데 부모클래스에서 virtual을 사용하면 오버라이드 되는 것이 문제는 없지만 만약 부모클래스를 찾을 수 없다면???
	// 부모클래스에서 virtual을 안해주면 오류가 발생한다!

	// override를 할 때는 보통 옆에 붙여준다, 실수도 줄여주고 가독성도 좋아지기 때문이다!

	return 0;
}