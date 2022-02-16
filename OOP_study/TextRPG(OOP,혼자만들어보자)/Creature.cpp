#include "Creature.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


void Creature::NomalAttack(Creature* attacker)
{
	int damage = 0;
	int Critical = rand() % 4 + 1; // 1~4의 숫자 랜덤 -> 25%?

	// 크리티컬 유무
	if (Critical == 1)
	{
		damage = (attacker->_attack * 2) - _defence;
		cout << "크리티컬!!!" << endl;
	}
	else
	{
		damage = attacker->_attack - _defence;
	}
	// 데미지 마이너스 예방
	if (damage <= 0)
		damage = 0;
	
	// hp 마이너스 예방
	_hp -= damage;
	if (_hp <= 0)
		_hp = 0;
}

