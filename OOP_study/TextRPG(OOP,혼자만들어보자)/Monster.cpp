#include "Monster.h"
#include <iostream>
using namespace std;

void Monster::PrintMonsterStatus()
{
	cout << "-------------------------------------------------" << endl;
	switch (Monster_monsterType)
	{
	case MT_SLIME:
		cout << "[슬라임]" << endl;
		break;

	case MT_ORC:
		cout << "[오크]" << endl;
		break;

	case MT_SKELETON:
		cout << "[스켈레톤]" << endl;
		break;
	}
	cout << "몬스터의 체력: " << _hp << endl;
	cout << "몬스터의 공격력: " << _attack << endl;
	cout << "몬스터의 방어력: " << _defence << endl;
	cout << "-------------------------------------------------" << endl;
}

void Monster::PrintMonsterHp()
{
	cout << "-------------------------------------------------" << endl;
	cout << "몬스터의 체력: " << _hp << endl;
	cout << "-------------------------------------------------" << endl;
}

bool Monster::MonsterIsDead()
{
	if (_hp <= 0)
		return true;
}

void Monster::SkillAttack(int damage)
{
	_hp -= (damage - _defence);
	if (_hp <= 0)
		_hp = 0;
}
