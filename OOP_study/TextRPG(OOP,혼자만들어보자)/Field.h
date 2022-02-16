#pragma once

// ���漱���� �غ��ô�
class Player;
class Monster;

class Field
{
public:
	Monster* _monster;
	int MonsterKind;
	int SlimeKillCount;
	int OrcKillCount;
	int SkeletonKillCount;

public:
	Field();
	~Field();
	
	void MonsterUpdate(Player* player);
	//1) ���͸� ����
	//2) ��Ʋ ����
	
	void CreateMonster();
	// 1) ���� ���� ���� (0~2)
	// 2) ���� �����ڸ� �����.
	// 3) ������ ���¸� ǥ���Ѵ�.

	void StartBattle(Player* player);
	// 1) ������ ���¸� ǥ���Ѵ�.
	// 1.���� 2.��ų 3.�÷��̾� ����ǥ�� 4. ����(10%)

	void KillCount();
};

