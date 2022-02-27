#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

class Knight
{
public:

private:
	void operator=(const Knight& k); // 정의되지 않은 함수 -> 이런 식으로 옛날에는 사용되지 않게 막았었다.
	void operator=(const Knight& k) = delete; // 이런 식으로 사용하면 출력에 삭제된 함수라고 표시가 된다!!

	friend class Admin; // private권한을 열어준다! (거의 안씀)

private:
	int _hp = 100;
};

class Admin
{
public:
	void CopyKnight(const Knight& k)
	{
		Knight k1;

		// 복사연산자
		k1 = k; // operator가 정의되어 있면 사용가능
	}
};

int main()
{
	// delete (삭제된 함수) -> new delete는 아님
	Knight k1;
	Knight k2;
	k2 = k1; //private 때문에 복사생성자가 막힘


	return 0;
}