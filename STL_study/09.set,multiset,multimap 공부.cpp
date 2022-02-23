#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

int main()
{
	/* set !!
	map 같은 경우는 (key, value)를 사용한다.
	하지만 아예 데이터 자체를 key로 사용할 수도 있다!!!
	map이 쓰던 넣고,빼고,찾고,순회하는 방법이 똑같다.
	set은 맵과 달리 s[0] = 10; 이 막혀있다. (키가 곧 value이기 때문??)
	*/
	map<int, int> map;
	set<int> s;

	// 1) 넣기
	s.insert(10);
	s.insert(30);
	s.insert(20);
	s.insert(50);
	s.insert(40);

	// 2) 빼기
	s.erase(40);

	// 3) 찾기
	set<int>::iterator findit = s.find(50);
	if (findit == s.end())
	{
		cout << "못 찾음" << endl;
	}
	else
	{
		cout << "찾음" << endl;
	}

	//4) 순회하기
	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << (*it) << endl;
	}

	cout << "---------------------" << endl;
	/* multimap, multiset (자주 안쓰이긴 함)
	map에서 중복키를 허용하는 것이 multimap, set에서 중복키를 허용하는 것이 multiset

	*/

	multimap<int, int> mm;

	// 1) 넣기
	mm.insert(make_pair(1, 100));
	mm.insert(make_pair(1, 200));
	mm.insert(make_pair(1, 300));
	mm.insert(make_pair(2, 400));
	mm.insert(make_pair(2, 500));

	// mm[1] = 500; 이거는 막혀있음
	// 2) 빼기
	//unsigned int count = mm.erase(1); // 키(중복) 값에 포함되는 모든 값이 삭제된다!

	// 3) 찾기
	/*multimap<int,int>::iterator itfind = mm.find(1); // mm.find(1)은 첫번째로 만족하는 애만 찾아줌 (1, 100)
	++itfind;  // 다음과 같이 넣어주면 (1,100)이 아니라 (1,200)이 삭제가 된다!!
	if (itfind != mm.end())
	mm.erase(itfind);*/

	// 4) 순회하기
	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> itPair;
	itPair = mm.equal_range(1); // (1,100)의 영역과 (2,400)의 영역을 따로 빼준다!

	multimap<int, int>::iterator itBegin = mm.lower_bound(1); // 1이 시작하는 영역
	multimap<int, int>::iterator itEnd = mm.upper_bound(1); // 1이 끝나는 다음 영역

	for (multimap<int, int>::iterator it = itPair.first; it != itPair.second; ++it) //first는 (1,100)을 가르키고 second는 (2,400)을 가르킨다.
	{
		cout << it->first << " " << it->second << endl;
	}

	cout << "---------------------" << endl;

	multiset<int> ms;

	// 1) 넣기
	ms.insert(100);
	ms.insert(100);
	ms.insert(100);
	ms.insert(200);
	ms.insert(200);

	// 2) 찾기
	multiset<int>::iterator findit2 = ms.find(100);

	pair<multiset<int>::iterator, multiset<int>::iterator> itPair2;
	itPair2 = ms.equal_range(100);

	for (multiset<int>::iterator it = itPair2.first; it != itPair2.second; ++it) {
		cout << *it << endl;
	}

	multiset<int>::iterator itBegin2 = ms.lower_bound(100);
	multiset<int>::iterator itEnd2 = ms.upper_bound(100);


	for (multiset<int>::iterator it = itBegin2; it != itEnd2; ++it) {
		cout << *it << endl;
	}
	return 0;
}