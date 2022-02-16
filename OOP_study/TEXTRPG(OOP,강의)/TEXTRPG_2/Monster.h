#pragma once
#include "Creature.h"

/*
	Monster.h
	- 몬스터 종류 정의
	- 몬스터 상태 표시
*/

enum MonsterType
{
	MT_SLIME = 1,
	MT_ORC,
	MT_SKELETON
};

class Monster : public Creature
{
public:
	int _monsterType;

public:
	Monster(int MonsterType)
		: _monsterType(MonsterType), Creature(CT_MONSTER)
	{

	}

	~Monster()
	{

	}

	void PrintInfo();
};

class Slime : public Monster
{
public:
	Slime() : Monster(MT_SLIME)
	{
		_hp = 50;
		_attack = 5;
		_defence = 2;
	}
};

class Orc : public Monster
{
public:
	Orc() : Monster(MT_ORC)
	{
		_hp = 100;
		_attack = 8;
		_defence = 3;
	}
};

class Skeleton : public Monster
{
public:
	Skeleton() : Monster(MT_SKELETON)
	{
		_hp = 100;
		_attack = 10;
		_defence = 4;
	}
};