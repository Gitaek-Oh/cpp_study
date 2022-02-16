#pragma once
/*
	Creature.h (최상위 부모?)
	- 플레이어 몬스터 구분
	- 사망 여부 확인
	- 공격 상황
	- 프린트 (가상함수)
	후.... 만들어 보자
*/
enum CreatureType
{
	CT_PLAYER = 0,
	CT_MONSTER
};

class Creature
{
protected:
	int _creatureType;
	int _hp = 0;
	int _attack = 0;
	int _defence = 0;

public:
	Creature(int CreatureType) : _creatureType(CreatureType)
	{

	}

	// 최상위 부모에 가상함수를 붙이면.... 
	// vftable에 생성자들이 들어가기 때문에 가상함수가 소멸되면 모든 생성자들이 소멸된다?
	// -> 메모리 낭비 X, 그렇다면 왜 생성자는 가상함수를 안붙이는가....? 물어봐야 겠다....
	virtual ~Creature()
	{

	}

	virtual void PrintInfo() = 0;

	bool IsDead() { return _hp <= 0; }
	void OnAttacked(Creature* attacker);
};