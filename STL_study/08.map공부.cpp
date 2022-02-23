#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>

class Player
{
public:
	Player() : _playerId(0) { }
	Player(int playerId)
	{
		_playerId = playerId;
	}

public:
	int _playerId;
};

int main()
{
	/* vector와 list를 쓰면 좋은 데 치명적인 단점이 있다!!
	vector< Player*> v;

	10만명 입장
	for (int i = 0; i < 100000; i++)
	{
	Player* p = new Player(i);
	v.push_back(p);
	}

	5만명이 퇴장
	for (int i = 0; i < 50000; i++)
	{
	int randIndex = rand() % v.size();

	Player* p = v[randIndex];
	delete p;

	v.erase(v.begin() + randIndex);
	}

	Q) ID = 1만 인 Player를 찾아주세요
	A) 하나하나 찾아본다.

	bool found = false;
	for (int i = 0; i < v.size(); i++)
	{
	if (v[i]->_playerId == 10000)
	{
	found = true;
	break;
	}
	}

	vector, list의 치명적인 단점
	-> 원하는 조건에 해당하는 데이터를 빠르게 찾을 수 없다!!! ****************************************************
	-> 그러면 다른 방법으로 데이터를 저장해야하는 데... 연관 컨테이너로 다르게 저장할 수 있다!*/

	/* 연관 컨테이너
	map: 균형 이진 트리 (AVL) -> 작은 값은 왼쪽에 큰 값은 오른쪽에 (구글에 검색해서 그림 참조)
	- 노드 기반
	*/
	srand(static_cast<unsigned int>(time(nullptr)));
	class Node
	{
	public:
		Node* _left;
		Node* _right;
		// DATA
		pair<int, Player*> _data; // pair는 그냥 데이터 2개를 저장하는 거랑 닽다고 생각하면 된다.
		// int _key;
		// Player* _value;
	};

	// (key, value)
	map<int, int> m;

	/* 만약에 없는 데이터를 삽입하라고 명령을 하면??
	똑같은 키에 값을 여러번 삽입하면? -> 두 번째 요청이 씹히게 된다.
	m.insert(make_pair(1,100));
	m.insert(make_pair(1,200));

	// insert를 살펴보면 아래와 같다!!!
	pair<map<int, int>::iterator, bool> ok;
	ok = m.insert(make_pair(1, 100)); // first = (1 , 100), second = true
	ok = m.insert(make_pair(1, 200)); // first = (1 , 100), second = false
	-> 혹시라도 동일한 키가 있더라면 그 값을 덮어쓰는게 아니라 무시된다는걸 알 수있다.*/

	// 10만명 입장
	for (int i = 0; i < 100000; i++)
	{
		m.insert(pair<int, int>(i, i * 100)); // i = key, i*100 = _value
	}

	// 5만명 퇴장
	for (int i = 0; i < 50000; i++)
	{
		int randValue = rand() % 50000;

		// Erase by Key
		m.erase(randValue);
	}
	/* 만약에 없는 데이터를 삭제하라고 명령을 하면??
	unsigned int count = 0; // erase가 size_t를 반환해주는 데 이것은 unsigned int라고 보면 된다.
	count = m.erase(10000); // count = 1
	count = m.erase(10000); // count = 0
	-> erase를 여러번 호출해도 문제가 되지 않는다. 중복되더라고 삭제요청이 씹히는 일이 발생한다 */

	// Q) ID = 1만인 Player 찾고 싶다!
	// A) 매우 빠르게 찾을 수 있음

	map<int, int>::iterator findIt = m.find(10000);
	if (findIt != m.end()) // 값을 못찾았으면 m.end() 값을 가지고 있는다
	{
		cout << "찾음" << endl;
	}
	else
	{
		cout << "못찾음" << endl;
	}

	/* map 순회
	vector는 v[0] ~ v[i]처럼 연속적으로 있어서 순회할 수 있지만
	map 같은 경우는 위에 있는 문법을 쓰면 안되고 iterator를 써야한다.*/

	for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		pair<const int, int>& p = (*it); // (*it)는 앞에 나온 pair형태로 되있다. key값은 const다
		// key 값과 value 값을 따로 추출해서 볼 수 있다.
		int key = it->first; // (*it).first
		int value = it->second;
		cout << key << " " << value << endl;
	}

	// 없으면 추가하고 있으면 수정하는 방법
	map<int, int>::iterator findIt = m.find(10000);
	if (findIt != m.end()) // 값을 못찾았으면 m.end() 값을 가지고 있는다
	{
		// key가 있으면 sencond에 접근해서 value값 수정
		findIt->second = 200;
	}
	else
	{
		// 없으면 추가
		m.insert(make_pair(10000, 10000));
	}

	/* 없으면 추가하고 있으면 수정하는 방법 ver.2
	5라는 키값이 없으면 추가하고 value를 500으로 추가
	5라는 키값이 있으면 value를 500으로 수정*/
	m[5] = 500;

	// [] 연산자 사용할 때 주의
	// 대입을 하지 않더라도 (Key/Value) 형태의 데이터가 추가된다!!
	m.clear();
	for (int i = 0; i < 10; i++)
	{
		cout << m[i] << endl;
	}
	// -> 이렇게 사용하는 순간 키 값을 찾는 것도 있지만 없으면 데이터를 추가하기 때문에 주의해야한다!

	// 지금까지 map은
	// 넣고 (insert, [])
	// 빼고 (erase)
	// 찾고 (find, [])
	// 반복자 (map::iterator) (*it) pair<key, value>&


	return 0;
}