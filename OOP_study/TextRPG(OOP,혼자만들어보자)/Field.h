#pragma once

// 전방선언을 해봅시다
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
	//1) 몬스터를 생성
	//2) 배틀 시작
	
	void CreateMonster();
	// 1) 랜덤 값을 생성 (0~2)
	// 2) 몬스터 생성자를 만든다.
	// 3) 몬스터의 상태를 표시한다.

	void StartBattle(Player* player);
	// 1) 몬스터의 상태를 표시한다.
	// 1.공격 2.스킬 3.플레이어 상태표시 4. 도망(10%)

	void KillCount();
};

