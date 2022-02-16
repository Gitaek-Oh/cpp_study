#pragma once
#include "Creature.h"



enum PlayerType
{
	PT_KNIGHT = 0,
	PT_MAGE,
};

enum PlayerTurn
{
	P_ATTACK = 2,
	P_SKILL,
	P_RUN
};

class Player : public Creature
{
public:
	int Player_playerType;

public:
	Player(int PlayerType) : Player_playerType(PlayerType), Creature(CT_PLAYER)
	{

	}
	~Player()
	{

	}

	int PlayerTurn();			// 행동선택
	int SkillAttack();			// 플레이어 스킬공격
	void PrintPlayerStatus();	// 플레이어 상태표시
};

class Knight : public Player
{
public:
	Knight() : Player(PT_KNIGHT)
	{
		_hp = 200;
		_player_mp = 80;
		_attack = 10;
		_defence = 5;
	}
	~Knight()
	{

	}
};

class Mage : public Player
{
public:
	Mage() : Player(PT_MAGE)
	{
		_hp = 100;
		_player_mp = 150;
		_attack = 20;
		_defence = 3;
	}
	~Mage()
	{

	}
};