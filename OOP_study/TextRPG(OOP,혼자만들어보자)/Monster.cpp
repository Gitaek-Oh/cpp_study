#include "Monster.h"
#include <iostream>
using namespace std;

void Monster::PrintMonsterStatus()
{
	cout << "-------------------------------------------------" << endl;
	switch (Monster_monsterType)
	{
	case MT_SLIME:
		cout << "[������]" << endl;
		break;

	case MT_ORC:
		cout << "[��ũ]" << endl;
		break;

	case MT_SKELETON:
		cout << "[���̷���]" << endl;
		break;
	}
	cout << "������ ü��: " << _hp << endl;
	cout << "������ ���ݷ�: " << _attack << endl;
	cout << "������ ����: " << _defence << endl;
	cout << "-------------------------------------------------" << endl;
}

void Monster::PrintMonsterHp()
{
	cout << "-------------------------------------------------" << endl;
	cout << "������ ü��: " << _hp << endl;
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
