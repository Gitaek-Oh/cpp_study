#include "Creature.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


void Creature::NomalAttack(Creature* attacker)
{
	int damage = 0;
	int Critical = rand() % 4 + 1; // 1~4�� ���� ���� -> 25%?

	// ũ��Ƽ�� ����
	if (Critical == 1)
	{
		damage = (attacker->_attack * 2) - _defence;
		cout << "ũ��Ƽ��!!!" << endl;
	}
	else
	{
		damage = attacker->_attack - _defence;
	}
	// ������ ���̳ʽ� ����
	if (damage <= 0)
		damage = 0;
	
	// hp ���̳ʽ� ����
	_hp -= damage;
	if (_hp <= 0)
		_hp = 0;
}

