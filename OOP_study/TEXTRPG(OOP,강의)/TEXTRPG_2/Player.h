#pragma once
#include "Creature.h"

/*
	Player.h 
	- 플레이어 직업 정의
	- 플레이어 상태 표시
*/

enum PlayerType
{
	PT_KNIGHT = 1,
	PT_ARCHER,
	PT_MAGE
};

class Player : public Creature
{
public :
	int _playerType;

public:
	Player(int PlayerType) 
		: _playerType(PlayerType), Creature(CT_PLAYER)
	{

	}

	~Player()
	{

	}

	void PrintInfo();
};

class Knight : public Player
{
public:
	Knight() : Player(PT_KNIGHT)
	{
		_hp = 200;
		_attack = 10;
		_defence = 5;
	}
};

class Archer : public Player
{
public:
	Archer() : Player(PT_ARCHER)
	{
		_hp = 150;
		_attack = 15;
		_defence = 3;
	}
};

class Mage : public Player
{
public:
	Mage() : Player(PT_MAGE)
	{
		_hp = 80;
		_attack = 25;
		_defence = 3;
	}
};