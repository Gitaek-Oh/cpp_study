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
	int RandValue = rand() % 3; // 0~2������ ���ڸ� ����
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
	// 1) ���� ����ǥ��
	cout << "!!!!!!!!!!!!! ���Ͱ� �����߽��ϴ�. �����غ� !!!!!!!!!!!!!!!!!!" << endl;
	_monster->PrintMonsterStatus();
}

void Field::StartBattle(Player* player)
{

	while (true) // �÷��̾� �ൿ
	{
		int damage = 0;
		int PlayerChoice = player->PlayerTurn(); // PlayerTurn(): �÷��̾� �ൿ����
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
			int RunChance = rand() % 10 + 1; // 10% Ȯ��
			if (RunChance == 1)
			{
				cout << "��������!!!" << endl;
				delete _monster;
				_monster = nullptr;
				break;
			}
			else cout << "��������!!!" << endl;
		}

		
		_monster->PrintMonsterHp();

		if (_monster->IsDead())
		{
			cout << "���͸� óġ�Ͽ����ϴ�!!!!" << endl;
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
			cout << " ���� ������ ��: " << SlimeKillCount << endl;
			cout << " ���� ��ũ ��: " << OrcKillCount << endl;
			cout << " ���� ���̷��� ��: " << SkeletonKillCount << endl;
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