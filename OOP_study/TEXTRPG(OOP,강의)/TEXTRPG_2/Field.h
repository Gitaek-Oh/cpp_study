#pragma once

/*
	Field.h
	- 몬스터 생성.....
	- 배틀 시작.....
*/

class Monster;
class Player;

class Field
{
public:
	Monster* _monster;

public:
	Field();
	~Field();
	
	void Update(Player* player);
	void CreateMonster();
	void StartBattle(Player* player);
};