#pragma once
#include "Creature.h"

enum MonsterType
{
	MT_SLIME = 0,
	MT_ORC,
	MT_SKELETON,
};
class Monster : public Creature
{
public:
	int Monster_monsterType;

public:
	Monster(int MonsterType) : Monster_monsterType(MonsterType), Creature(CT_MONSTER)
	{

	}
	~Monster()
	{

	}

	void PrintMonsterStatus();
	void PrintMonsterHp();
	bool MonsterIsDead();
	void SkillAttack(int damage);
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
	~Slime()
	{

	}
};

class Orc : public Monster
{
public:
	Orc() : Monster(MT_ORC)
	{
		_hp = 80;
		_attack = 7;
		_defence = 3;
	}
	~Orc()
	{

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
	~Skeleton()
	{

	}
};
