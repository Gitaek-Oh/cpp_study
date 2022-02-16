#pragma once

/*
	Field.h
	- ���� ����.....
	- ��Ʋ ����.....
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