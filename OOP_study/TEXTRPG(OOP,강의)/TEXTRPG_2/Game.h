#pragma once

/*
	Game.h
	- �ʱ�ȭ �Լ�
	- while�� Update�Լ�
	�÷��̾�� �ʵ带 �ҷ��� �ʱ�ȭ���ش�, �ʵ忡�� ���Ͱ� �ִ�.
*/

// ���漱��... �ش� Ŭ������ ���� ���̶�� �̸� �������ش�...?
class Player;
class Field;

class Game
{
public:
	Player* _player;
	Field* _field;

public:
	Game();
	~Game();
	void Update();
	void CreatePlayer();
	void Init();
};