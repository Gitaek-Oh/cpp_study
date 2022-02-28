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
	Knight() { cout << "Knight 생성" << endl; }
	~Knight() { cout << "Knight 소멸" << endl; }
	void Attack()
	{
		if (_target)
		{
			_target->_hp -= _damage;
			cout << "HP: " << _target->_hp << endl;
		}
	}
public:
	int _hp = 100;
	int _damage = 10;
	shared_ptr<Knight> _target = nullptr;

};

class RefCountBlock
{
public:
	int _refCount = 1; // 몇명이 해당 객체를 참고하는지 확인하는 카운트
};

template<typename T>
class SharedPtr
{
public:
	SharedPtr() { }
	SharedPtr(T* ptr)
	{
		_ptr = ptr;
		if (_ptr != nullptr)
		{
			_block = new RefCountBlock();
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	SharedPtr(const SharedPtr& sptr)
	{
		_ptr = sptr._ptr;
		_block = sptr._block;
		if (_ptr!-= nullptr)
		{
			_block->_refCount++;
			cout << "RefCount : " << _block->_refCount << endl;

		}
	}

	auto operator=(const SharedPtr& ptr)
	{
		_ptr = sptr._ptr;
		_block = sptr._block;
	}

	~SharedPtr()
	{
		if (_ptr != nullptr)
		{
			_block->_refCount--;
			cout << "RefCount : " << _block->_refCount << endl;

			if (_block->_refCount == 0)
			{
				delete _ptr;
				delete _block;
				cout << "Delete Data" << endl;
			}
		}
	}
public:
	T* _ptr = nullptr;
	RefCountBlock* _block
};

int main()
{
	/*Knight* k1 = new Knight();
	Knight* k2 = new Knight();

	k1->_target = k2;

	delete k2;

	k1->Attack();*/ // k2가 삭제가되서 쓰레기 값이 나온다.

	// 스마트 포인터 (smart pointer) : 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
	// shared_ptr, weak_ptr, unique_ptr

	/*SharedPtr<Knight> k2;
	{
	SharedPtr<Knight> k1(new Knight());
	k2 = k1;
	}*/

	shared_ptr<Knight> k1 = make_shared<Knight>(); // new로 만드는 것 보다 훨씬 빠르다
	{
		shared_ptr<Knight> k2 = make_shared<Knight>();
		k1->_target = k2;
	}

	k1->Attack(); // k2가 누군가는 기억을 하고있기 때문에 정확한 값이 나온다!

	/*shared_ptr의 단점은
	k1->_target = k2;
	k2->_target = k1;
	다음과 같이 순환형식이 되었을 때 Knight가 소멸이 안된다! -> 메모리가 해지가 안되서 메모리 고갈로 크래시난다
	안전하게하려면
	k1->target = nullptr;
	k2->target = nullptr;
	위의 코드와 같이 nullptr을 해주면 소멸이 된다!*/

	unique_ptr<Knight> uptr = make_unique<Knight>();
	unique_ptr<Knight> uptr2 = uptr; // 유니크이기 때문에 오류가 발생한다!!
	unique_ptr<Knight> uptr3 = std::move(uptr); // 오류가 발생하지 않는다! 원본자체를 움직였기 때문에!
	return 0;
}