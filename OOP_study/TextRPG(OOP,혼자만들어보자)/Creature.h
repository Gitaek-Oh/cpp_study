#pragma once

enum CreatureType
{
	CT_PLAYER = 0,
	CT_MONSTER,
};
class Creature
{
public:
	int _creatureType;
	int _hp = 0;
	int _player_mp = 0;
	int _attack = 0;
	int _defence = 0;

public:
	Creature(int CreatureType) :_creatureType(CreatureType)
	{

	}

	virtual ~Creature()
	{

	}

	bool IsDead() { return _hp <= 0; }
	void NomalAttack(Creature* attacker);

};

