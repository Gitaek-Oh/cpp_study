#include "Field.h"
#include "Monster.h"
#include "Player.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Field::Field()
{
	_monster = nullptr;
}

Field::~Field()
{
	if (_monster != nullptr)
		delete _monster;
}

void Field::MonsterUpdate(Player* player)
{
	if (_monster == nullptr)
		CreateMonster();
	StartBattle(player);
}

void Field::CreateMonster()
{
	int RandValue = rand() % 3; // 0~2까지의 숫자를 생성
	switch (RandValue)
	{
	case MT_SLIME:
		_monster = new Slime();
		MonsterKind = MT_SLIME;
		break;

	case MT_ORC:
		_monster = new Orc();
		MonsterKind = MT_ORC;
		break;

	case MT_SKELETON:
		_monster = new Skeleton();
		MonsterKind = MT_SKELETON;
		break;
	}
	// 1) 몬스터 상태표시
	cout << "!!!!!!!!!!!!! 몬스터가 등장했습니다. 전투준비 !!!!!!!!!!!!!!!!!!" << endl;
	_monster->PrintMonsterStatus();
}

void Field::StartBattle(Player* player)
{

	while (true) // 플레이어 행동
	{
		int damage = 0;
		int PlayerChoice = player->PlayerTurn(); // PlayerTurn(): 플레이어 행동선택
		switch (PlayerChoice)
		{
		case P_ATTACK:
			_monster->NomalAttack(player);
			break;

		case P_SKILL:
			damage = player->SkillAttack();
			_monster->SkillAttack(damage);
			break;
		}

		if (PlayerChoice == P_RUN)
		{
			int RunChance = rand() % 10 + 1; // 10% 확률
			if (RunChance == 1)
			{
				cout << "도망성공!!!" << endl;
				delete _monster;
				_monster = nullptr;
				break;
			}
			else cout << "도망실패!!!" << endl;
		}

		
		_monster->PrintMonsterHp();

		if (_monster->IsDead())
		{
			cout << "몬스터를 처치하였습니다!!!!" << endl;
			KillCount();
			delete _monster;
			_monster = nullptr;
			break;
		}

		player->NomalAttack(_monster);
		player->PrintPlayerStatus();

		if (player->IsDead())
		{
			cout << "-------------------------------------------------" << endl;
			cout << "------------------Game Over!!!!------------------" << endl;
			cout << " 죽인 슬라임 수: " << SlimeKillCount << endl;
			cout << " 죽인 오크 수: " << OrcKillCount << endl;
			cout << " 죽인 스켈레톤 수: " << SkeletonKillCount << endl;
			cout << "-------------------------------------------------" << endl;
			break;
		}
	}
}

void Field::KillCount()
{
	if (MonsterKind == MT_SLIME)
		SlimeKillCount++;
	else if (MonsterKind == MT_ORC)
		OrcKillCount++;
	else if (MonsterKind == MT_SKELETON)
		SkeletonKillCount++;
}